#include "lux/output.h"
#include "lux/tools.h"
#include "lux/gl.h"

#include "../xdg-shell-client-protocol.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <EGL/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>

//
//  private
//

struct _lx_window
{
    struct wl_display* wl_display;
    struct wl_registry* registry;
    struct wl_compositor* compositor;
    struct wl_surface* wl_surface;
    struct xdg_wm_base* wm_base;
    struct xdg_surface* xdg_surface;
    struct xdg_toplevel* toplevel;

    EGLDisplay* egl_display;
    EGLContext* egl_context;
    struct wl_egl_window* egl_window;
    EGLSurface* egl_surface;

    int is_alive;
};

void registry_global(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version)
{
    lx_window* window = data;

    if (strcmp(interface, "wl_compositor") == 0)
    {
        window->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);
    }

    if (strcmp(interface, "xdg_wm_base") == 0)
    {
        window->wm_base = wl_registry_bind(registry, name, &xdg_wm_base_interface, version);
    }
}

void registry_remove(void* data, struct wl_registry* registry, uint32_t name)
{
}

struct wl_registry_listener registry_listener =
{
    .global = registry_global,
    .global_remove = registry_remove
};

void wm_base_ping(void* data, struct xdg_wm_base* wm_base, uint32_t serial)
{
    xdg_wm_base_pong(wm_base, serial);
}

struct xdg_wm_base_listener wm_base_listener =
{
    .ping = wm_base_ping
};

void toplevel_close(void* data, struct xdg_toplevel* toplevel)
{
    lx_window* window = data;
    window->is_alive = 0;
}

void toplevel_configure(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height, struct wl_array* states)
{
    if (width> 0 && height > 0)
    {
        lx_window* window = data;
        wl_egl_window_resize(window->egl_window, width, height, 0, 0);
        glViewport(0, 0, width, height);
    }
}

void toplevel_configure_bounds(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height)
{
}

void topevel_wm_capabilities(void* data, struct xdg_toplevel* xdg_toplevel, struct wl_array* capabilities)
{
}

struct xdg_toplevel_listener toplevel_listener =
{
    .close = toplevel_close,
    .configure = toplevel_configure,
    .configure_bounds = toplevel_configure_bounds,
    .wm_capabilities = topevel_wm_capabilities
};

void surface_configure(void* data, struct xdg_surface* xdg_surface, uint32_t serial)
{
    xdg_surface_ack_configure(xdg_surface, serial);
}

struct xdg_surface_listener surface_listener =
{
    .configure = surface_configure
};

//
//  public
//

lx_window* lx_window_create(const char* title, int width, int height)
{
    lx_window* window = malloc(sizeof(struct _lx_window));
    if (!window)
    {
        lx_set_last_error("failed to allocate lx_window");
        return NULL;
    }
    lx_debug("allocated lx_window");

    window->wl_display = wl_display_connect(NULL);
    if (!window->wl_display)
    {
        lx_set_last_error("failed to connect to wayland display");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("connected to wayland display");

    window->registry = wl_display_get_registry(window->wl_display);
    if (!window->registry)
    {
        lx_set_last_error("failed to get wayland display registry");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("got wayland registry");

    wl_registry_add_listener(window->registry, &registry_listener, window);
    if (wl_display_roundtrip(window->wl_display) < 0)
    {
        lx_set_last_error("failed to get wayland globals");
        lx_window_destroy(window);
        return NULL;
    }

    if (!window->compositor) // set by wl_display_roundtrip and the registry_global callback
    {
        lx_set_last_error("failed to get wayland compositor");
        lx_window_destroy(window);
        return NULL;
    }

    if (!window->wm_base) // set by wl_display_roundtrip and the registry_global callback
    {
        lx_set_last_error("failed to get wayland wm base");
        lx_window_destroy(window);
        return NULL;
    }

    xdg_wm_base_add_listener(window->wm_base, &wm_base_listener, NULL);
    lx_debug("retrieved wayland globals");

    window->wl_surface = wl_compositor_create_surface(window->compositor);
    if (!window->wl_surface)
    {
        lx_set_last_error("failed to create a wayland surface");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created wayland surface");

    window->xdg_surface = xdg_wm_base_get_xdg_surface(window->wm_base, window->wl_surface);
    if (!window->xdg_surface)
    {
        lx_set_last_error("failed to create xdg surface");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created xdg surface");

    window->toplevel = xdg_surface_get_toplevel(window->xdg_surface);
    if (!window->toplevel)
    {
        lx_set_last_error("failed to create xdg toplevel");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created xdg toplevel");

    xdg_toplevel_set_title(window->toplevel, title);
    xdg_toplevel_set_app_id(window->toplevel, title);
    xdg_surface_add_listener(window->xdg_surface, &surface_listener, NULL);
    xdg_toplevel_add_listener(window->toplevel, &toplevel_listener, window);

    wl_surface_commit(window->wl_surface);
    lx_debug("committed initial surface");

    window->egl_display = eglGetDisplay((EGLNativeDisplayType)window->wl_display); 
    if (window->egl_display == NULL || window->egl_display == EGL_NO_DISPLAY)
    {
        lx_set_last_error("failed to create egl display");
        lx_window_destroy(window);
        return NULL;
    }

    if (eglInitialize(window->egl_display, NULL, NULL) != EGL_TRUE)
    {
        lx_set_last_error("failed to initialise egl");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("initialised egl");

    EGLConfig config;
    EGLint num_configs;
    EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    if (eglChooseConfig(window->egl_display, attribs, &config, 1, &num_configs) != EGL_TRUE)
    {
        lx_set_last_error("failed to choose egl config");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("configured egl");

    EGLint context_attribs[] =
    {
        EGL_NONE
    };
    eglBindAPI(EGL_OPENGL_API);

    window->egl_context = eglCreateContext(window->egl_display, config, EGL_NO_CONTEXT, context_attribs);
    if (!window->egl_context)
    {
        lx_set_last_error("failed to create egl context");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created egl context");

    window->egl_window = wl_egl_window_create(window->wl_surface, width, height);
    if (!window->egl_window)
    {
        lx_set_last_error("failed to create egl window");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created egl window");

    window->egl_surface = eglCreateWindowSurface(window->egl_display, config, (EGLNativeWindowType)window->egl_window, NULL);
    if (window->egl_surface == EGL_NO_SURFACE)
    {
        lx_set_last_error("failed to create egl surface");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("created egl surface");

    if (!eglMakeCurrent(window->egl_display, window->egl_surface, window->egl_surface, window->egl_context))
    {
        lx_set_last_error("failed to make egl context current");
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("made egl context current");

    int version = lx_load_gl_procs();
    if (version == 0)
    {
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("loaded opengl version %d.%d", (version / 10000), (version % 10000));

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    window->is_alive = 1;
    return window;
}

void lx_window_destroy(lx_window* window)
{
    if (window->egl_surface != NULL)
    {
        eglDestroySurface(window->egl_display, window->egl_surface);
        lx_debug("destroyed egl surface");
    }

    if (window->egl_context != NULL)
    {
        eglDestroyContext(window->egl_display, window->egl_context);
        lx_debug("destroyed egl context");
    }

    if (window->egl_display != NULL)
    {
        eglTerminate(window->egl_display);
        lx_debug("terminated egl");
    }

    if (window->egl_window != NULL)
    {
        wl_egl_window_destroy(window->egl_window);
        lx_debug("destroyed egl window");
    }

    if (window->toplevel != NULL)
    {
        xdg_toplevel_destroy(window->toplevel);
        lx_debug("destroyed xdg toplevel");
    }

    if (window->xdg_surface != NULL)
    {
        xdg_surface_destroy(window->xdg_surface);
        lx_debug("destroyed xdg surface");
    }

    if (window->wl_surface != NULL)
    {
        wl_surface_destroy(window->wl_surface);
        lx_debug("destroyed wayland surface");
    }

    if (window->wm_base != NULL)
    {
        xdg_wm_base_destroy(window->wm_base);
        lx_debug("destroyed xdg wm base");
    }

    if (window->compositor != NULL)
    {
        wl_compositor_destroy(window->compositor);
        lx_debug("destroyed wayland compositor");
    }

    if (window->wl_display != NULL)
    {
        wl_display_disconnect(window->wl_display);
        lx_debug("disconnected from wayland display");
    }

    free(window);
    lx_debug("deallocated lx_window");
}

void lx_window_update(lx_window* window)
{
    wl_display_dispatch(window->wl_display);

    glClear(GL_COLOR_BUFFER_BIT);
}

void lx_window_render(lx_window* window)
{
    eglSwapBuffers(window->egl_display, window->egl_surface);
}

int lx_window_is_alive(lx_window* window)
{
    return window->is_alive;
}
