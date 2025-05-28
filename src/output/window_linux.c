#include "lux/output.h"
#include "lux/tools.h"
#include "lux/gl.h"

#include "../platform/xdg_linux.h"
#include "../gl/loader.h"
#include "../tools/debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <EGL/egl.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
#include <wayland-egl-core.h>
#include <wayland-egl.h>

//
//  private - definitions
//

struct _lx_window
{
    // wayland window
    struct wl_display* wl_display;
    struct wl_registry* wl_registry;
    struct wl_compositor* wl_compositor;
    struct wl_surface* wl_surface;

    // xdg shell
    struct xdg_wm_base* xdg_wm_base;
    struct xdg_surface* xdg_surface;
    struct xdg_toplevel* xdg_toplevel;

    // egl surface
    EGLDisplay* egl_display;
    EGLContext* egl_context;
    struct wl_egl_window* egl_window;
    EGLSurface* egl_surface;

    // static properties
    char title[32];
    int width;
    int height;
    
    // dynamic properties
    int is_alive;
};

//
//  private - callbacks
//

static void wl_registry_global(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version)
{
    lx_window* window = data;

    if (strcmp(interface, "wl_compositor") == 0)
        window->wl_compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);

    if (strcmp(interface, "xdg_wm_base") == 0)
        window->xdg_wm_base = wl_registry_bind(registry, name, &xdg_wm_base_interface, version);
}

static void wl_registry_remove(void* data, struct wl_registry* registry, uint32_t name)
{
}

static void xdg_wm_base_ping(void* data, struct xdg_wm_base* wm_base, uint32_t serial)
{
    xdg_wm_base_pong(wm_base, serial);
}

static void xdg_surface_configure(void* data, struct xdg_surface* surface, uint32_t serial)
{
    xdg_surface_ack_configure(surface, serial);
}

static void xdg_toplevel_close(void* data, struct xdg_toplevel* toplevel)
{
    lx_window* window = data;
    window->is_alive = 0;
}

static void xdg_toplevel_configure(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height, struct wl_array* states)
{
    if (width <= 0 || height <= 0)
        return;

    lx_window* window = data;
    wl_egl_window_resize(window->egl_window, width, height, 0, 0);
    glViewport(0, 0, width, height);
}

static void xdg_toplevel_configure_bounds(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height)
{
}

static void xdg_toplevel_wm_capabilities(void* data, struct xdg_toplevel* toplevel, struct wl_array* capabilities)
{
}

//
//  private - listeners
//

static struct wl_registry_listener wl_listener_registry = {
    .global = wl_registry_global,
    .global_remove = wl_registry_remove
};

static struct xdg_wm_base_listener xdg_listener_wm_base =
{
    .ping = xdg_wm_base_ping
};

static struct xdg_surface_listener xdg_listener_surface =
{
    .configure = xdg_surface_configure
};

static struct xdg_toplevel_listener xdg_listener_toplevel =
{
    .close = xdg_toplevel_close,
    .configure = xdg_toplevel_configure,
    .configure_bounds = xdg_toplevel_configure_bounds,
    .wm_capabilities = xdg_toplevel_wm_capabilities
};

//
//  private
//

static const char* create_wayland_window(lx_window* window)
{
    window->wl_display = wl_display_connect(NULL);
    if (!window->wl_display)
        return "failed to connect to wayland display";

    lx_debug("created wl display");

    window->wl_registry = wl_display_get_registry(window->wl_display);
    if (!window->wl_registry)
        return "failed to get wayland display registry";

    wl_registry_add_listener(window->wl_registry, &wl_listener_registry, window);
    lx_debug("created wl registry");
    
    if (wl_display_roundtrip(window->wl_display) < 0)
        return "failed to complete wayland round trip";

    if (!window->wl_compositor) // set by wl_display_roundtrip and the registry_global callback
        return "failed to get wayland compositor";

    lx_debug("created wl compositor");

    window->wl_surface = wl_compositor_create_surface(window->wl_compositor);
    if (!window->wl_surface)
        return "failed to create wayland surface";

    lx_debug("created wl surface");

    return NULL;
}

static void destroy_wayland_window(lx_window* window)
{
    if (window->wl_surface != NULL)
    {
        wl_surface_destroy(window->wl_surface);
        lx_debug("destroyed wl surface");
    }

    if (window->wl_compositor != NULL)
    {
        wl_compositor_destroy(window->wl_compositor);
        lx_debug("destroyed wl compositor");
    }

    if (window->wl_registry != NULL)
    {
        wl_registry_destroy(window->wl_registry);
        lx_debug("destroyed wl registry");
    }

    if (window->wl_display != NULL)
    {
        wl_display_disconnect(window->wl_display);
        lx_debug("destroyed wl display");
    }
}

static const char* create_xdg_shell(lx_window* window)
{
    if (!window->xdg_wm_base) // set by wl_display_roundtrip and the registry_global callback
        return "failed to get xdg wm base";

    xdg_wm_base_add_listener(window->xdg_wm_base, &xdg_listener_wm_base, NULL);
    lx_debug("created xdg wm base");

    window->xdg_surface = xdg_wm_base_get_xdg_surface(window->xdg_wm_base, window->wl_surface);
    if (!window->xdg_surface)
        return "failed to create xdg surface";

    xdg_surface_add_listener(window->xdg_surface, &xdg_listener_surface, NULL);
    lx_debug("created xdg surface");

    window->xdg_toplevel = xdg_surface_get_toplevel(window->xdg_surface);
    if (!window->xdg_toplevel)
        return "failed to create xdg toplevel";

    xdg_toplevel_set_title(window->xdg_toplevel, window->title);
    xdg_toplevel_set_app_id(window->xdg_toplevel, window->title);
    xdg_toplevel_add_listener(window->xdg_toplevel, &xdg_listener_toplevel, window);
    lx_debug("created xdg toplevel");

    return NULL;
}

static void destroy_xdg_shell(lx_window* window)
{
    if (window->xdg_toplevel != NULL)
    {
        xdg_toplevel_destroy(window->xdg_toplevel);
        lx_debug("destroyed xdg toplevel");
    }

    if (window->xdg_surface != NULL)
    {
        xdg_surface_destroy(window->xdg_surface);
        lx_debug("destroyed xdg surface");
    }

    if (window->xdg_wm_base != NULL)
    {
        xdg_wm_base_destroy(window->xdg_wm_base);
        lx_debug("destroyed xdg wm base");
    }
}

static const char* create_egl_surface(lx_window* window)
{
    window->egl_display = eglGetDisplay((EGLNativeDisplayType)window->wl_display); 
    if (window->egl_display == EGL_NO_DISPLAY)
        return "failed to create egl display";

    lx_debug("created egl display");
    
    if (eglInitialize(window->egl_display, NULL, NULL) != EGL_TRUE)
        return "failed to initialise egl";

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
        return "failed to choose egl config";

    EGLint context_attribs[] = { EGL_NONE };
    eglBindAPI(EGL_OPENGL_API);
    
    lx_debug("configured egl");

    window->egl_context = eglCreateContext(window->egl_display, config, EGL_NO_CONTEXT, context_attribs);
    if (!window->egl_context)
        return "failed to create egl context";

    lx_debug("created egl context");

    window->egl_window = wl_egl_window_create(window->wl_surface, window->width, window->height);
    if (!window->egl_window)
        return "failed to create egl window";

    lx_debug("created egl window");

    window->egl_surface = eglCreateWindowSurface(window->egl_display, config, (EGLNativeWindowType)window->egl_window, NULL);
    if (window->egl_surface == EGL_NO_SURFACE)
        return "failed to create egl surface";

    lx_debug("created egl surface");

    if (!eglMakeCurrent(window->egl_display, window->egl_surface, window->egl_surface, window->egl_context))
        return "failed to make egl context current";

    lx_debug("made egl context current"); 

    return NULL;
}

static void destroy_egl_surface(lx_window* window)
{
    if (window->egl_surface != NULL)
    {
        eglDestroySurface(window->egl_display, window->egl_surface);
        lx_debug("destroyed egl surface");
    }

    if (window->egl_window != NULL)
    {
        wl_egl_window_destroy(window->egl_window);
        lx_debug("destroyed egl window");
    }

    if (window->egl_context != NULL)
    {
        eglDestroyContext(window->egl_display, window->egl_context);
        lx_debug("destroyed egl context");
    }

    if (window->egl_display != NULL)
    {
        eglTerminate(window->egl_display);
        lx_debug("destroyed egl display");
    }
}

//
//  public
//

lx_window* lx_window_create(const char* title, int width, int height)
{
    PARAM_GUARD(title == NULL, ("could not create window with null title"), NULL);
    PARAM_GUARD(width < 1 || width > 7680 || height < 1 || height > 4320, ("could not create window with improper dimensions, expected 1x1 to 7680x4320 but got %dx%d", width, height), NULL);

    static lx_window* window = NULL;
    if (window != NULL)
    {
        lx_set_last_error("failed to create window because it already exists");
        return NULL;
    }

    window = malloc(sizeof(lx_window));
    if (!window)
    {
        lx_set_last_error("failed to allocate window struct");
        return NULL;
    }
    lx_debug("allocated window struct");

    snprintf(window->title, sizeof(window->title), "%s", title);
    window->width = width;
    window->height = height;
    window->is_alive = 1;

    const char* success = create_wayland_window(window);
    if (success != NULL)
    {
        lx_set_last_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    success = create_xdg_shell(window);
    if (success != NULL)
    {
        lx_set_last_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    success = create_egl_surface(window);
    if (success != NULL)
    {
        lx_set_last_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    int version = load_gl_procs();
    version = load_gl_procs();
    if (version == 0)
    {
        lx_window_destroy(window);
        return NULL;
    }
    lx_debug("loaded opengl version %d.%d", (version / 10000), (version % 10000));

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}

void lx_window_destroy(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not destroy null window"));

    destroy_egl_surface(window);
    destroy_xdg_shell(window);
    destroy_wayland_window(window);

    free(window);
    lx_debug("freed window struct");
}

void lx_window_update(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not update null window"));
    
    wl_display_dispatch(window->wl_display);
    glClear(GL_COLOR_BUFFER_BIT);
}

void lx_window_render(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not render null window"));
    eglSwapBuffers(window->egl_display, window->egl_surface);
}

int lx_window_is_alive(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not determine alive state of null window"), 0);
    return window->is_alive;
}
