#include "core.h"
#include "../debug/debug.h"
#include "../platform/xdg_linux.h"
#include "../platform/xdg_deco_linux.h"

#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <wayland-client-core.h>
#include <wayland-client.h>
#include <wayland-egl.h>

typedef struct _window_store
{
    struct wl_display* wl_display;
    struct wl_registry* wl_registry;
    struct wl_compositor* wl_compositor;
    struct wl_surface* wl_surface;

    struct xdg_wm_base* xdg_wm_base;
    struct xdg_surface* xdg_surface;
    struct xdg_toplevel* xdg_toplevel;
    struct zxdg_decoration_manager_v1* xdg_deco;

    EGLDisplay* egl_display;
    EGLContext* egl_context;
    struct wl_egl_window* egl_window;
    EGLSurface* egl_surface;

    double time_began;
    double last_frame_time;
    double cur_frame_time;
    double delta_time;
}
window_store;

// private source
// ---------------------------------------------------------------- 

static struct wl_keyboard_listener wl_listener_keyboard;
static struct wl_pointer_listener wl_listener_pointer;
static int xdg_ack = 0;

static void wl_registry_global(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version)
{
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        lt_store->window->wl_compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);

    if (strcmp(interface, xdg_wm_base_interface.name) == 0)
        lt_store->window->xdg_wm_base = wl_registry_bind(registry, name, &xdg_wm_base_interface, version);

    if (strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0)
        lt_store->window->xdg_deco = wl_registry_bind(registry, name, &zxdg_decoration_manager_v1_interface, version);
}

static void xdg_wm_base_ping(void* data, struct xdg_wm_base* wm_base, uint32_t serial)
{
    xdg_wm_base_pong(wm_base, serial);
}

static void xdg_surface_configure(void* data, struct xdg_surface* surface, uint32_t serial)
{
    xdg_surface_ack_configure(surface, serial);
    xdg_ack = 1;
}

static void xdg_toplevel_close(void* data, struct xdg_toplevel* toplevel)
{
    lt_store->alive = 0;
}

static void xdg_toplevel_configure(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height, struct wl_array* states)
{
    if (width <= 0 || height <= 0)
        return;

    lt_props.width = width;
    lt_props.height = height;

    wl_egl_window_resize(lt_store->window->egl_window, width, height, 0, 0);

    if (lt_props.on_resize != NULL)
        lt_props.on_resize(width, height);
}

static void xdg_toplevel_configure_bounds(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height)
{}

static void xdg_toplevel_wm_capabilities(void* data, struct xdg_toplevel* toplevel, struct wl_array* capabilities)
{}

static void wl_registry_global_remove(void* data, struct wl_registry* registry, uint32_t name)
{}

static struct wl_registry_listener wl_listener_registry =
{
    .global = wl_registry_global,
    .global_remove = wl_registry_global_remove 
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

static int create_wayland_window()
{
    lt_store->window->wl_display = wl_display_connect(NULL);
    if (!lt_store->window->wl_display)
    {
        emit_error("failed to connect to wayland display");
        return 0;
    }

    lt_store->window->wl_registry = wl_display_get_registry(lt_store->window->wl_display);
    if (!lt_store->window->wl_registry)
    {
        emit_error("failed to get wayland display registry");
        return 0;
    }

    wl_registry_add_listener(lt_store->window->wl_registry, &wl_listener_registry, NULL);

    if (wl_display_roundtrip(lt_store->window->wl_display) < 0)
    {
        emit_error("failed to complete wayland round trip");
        return 0;
    }

    if (!lt_store->window->wl_compositor)
    {
        emit_error("failed to get wayland compositor");
        return 0;
    }

    lt_store->window->wl_surface = wl_compositor_create_surface(lt_store->window->wl_compositor);
    if (!lt_store->window->wl_surface)
    {
        emit_error("failed to create wayland surface");
        return 0;
    }

    return 1;
}

static void destroy_wayland_window()
{
    if (lt_store->window->wl_surface != NULL)
        wl_surface_destroy(lt_store->window->wl_surface);

    if (lt_store->window->wl_compositor != NULL)
        wl_compositor_destroy(lt_store->window->wl_compositor);

    if (lt_store->window->wl_registry != NULL)
        wl_registry_destroy(lt_store->window->wl_registry);

    if (lt_store->window->wl_display != NULL)
        wl_display_disconnect(lt_store->window->wl_display);
}

static int create_xdg_shell()
{
    if (!lt_store->window->xdg_wm_base)
    {
        emit_error("failed to get xdg wm base");
        return 0;
    }

    xdg_wm_base_add_listener(lt_store->window->xdg_wm_base, &xdg_listener_wm_base, NULL);

    lt_store->window->xdg_surface = xdg_wm_base_get_xdg_surface(lt_store->window->xdg_wm_base, lt_store->window->wl_surface);
    if (!lt_store->window->xdg_surface)
    {
        emit_error("failed to create xdg surface");
        return 0;
    }

    xdg_surface_add_listener(lt_store->window->xdg_surface, &xdg_listener_surface, NULL);

    lt_store->window->xdg_toplevel = xdg_surface_get_toplevel(lt_store->window->xdg_surface);
    if (!lt_store->window->xdg_toplevel)
    {
        emit_error("failed to create xdg toplevel");
        return 0;
    }

    xdg_toplevel_set_title(lt_store->window->xdg_toplevel, lt_props.title);
    xdg_toplevel_set_app_id(lt_store->window->xdg_toplevel, lt_props.title);
    xdg_toplevel_add_listener(lt_store->window->xdg_toplevel, &xdg_listener_toplevel, NULL);

    if (lt_store->window->xdg_deco)
    {
        struct zxdg_toplevel_decoration_v1* deco = zxdg_decoration_manager_v1_get_toplevel_decoration(lt_store->window->xdg_deco, lt_store->window->xdg_toplevel); 
        zxdg_toplevel_decoration_v1_set_mode(deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
    }

    wl_surface_commit(lt_store->window->wl_surface);
    while (xdg_ack == 0)
        wl_display_dispatch(lt_store->window->wl_display);

    return 1;
}

static void destroy_xdg_shell()
{
    if (lt_store->window->xdg_toplevel != NULL)
        xdg_toplevel_destroy(lt_store->window->xdg_toplevel);

    if (lt_store->window->xdg_surface != NULL)
        xdg_surface_destroy(lt_store->window->xdg_surface);

    if (lt_store->window->xdg_wm_base != NULL)
        xdg_wm_base_destroy(lt_store->window->xdg_wm_base);
}

static int create_egl_surface()
{
    lt_store->window->egl_display = eglGetDisplay((EGLNativeDisplayType)lt_store->window->wl_display); 
    if (lt_store->window->egl_display == EGL_NO_DISPLAY)
    {
        emit_error("failed to create egl display");
        return 0;
    }

    if (eglInitialize(lt_store->window->egl_display, NULL, NULL) != EGL_TRUE)
    {
        emit_error("failed to initialise egl");
        return 0;
    }

    EGLConfig config;
    EGLint num_configs;
    EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    if (eglChooseConfig(lt_store->window->egl_display, attribs, &config, 1, &num_configs) != EGL_TRUE)
    {
        emit_error("failed to choose egl config");
        return 0;
    }

    EGLint context_attribs[] = { EGL_NONE };
    eglBindAPI(EGL_OPENGL_API);
    
    lt_store->window->egl_context = eglCreateContext(lt_store->window->egl_display, config, EGL_NO_CONTEXT, context_attribs);
    if (!lt_store->window->egl_context)
    {
        emit_error("failed to create egl context");
        return 0;
    }

    lt_store->window->egl_window = wl_egl_window_create(lt_store->window->wl_surface, lt_props.width, lt_props.height);
    if (!lt_store->window->egl_window)
    {
        emit_error("failed to create egl window");
        return 0;
    }

    lt_store->window->egl_surface = eglCreateWindowSurface(lt_store->window->egl_display, config, (EGLNativeWindowType)lt_store->window->egl_window, NULL);
    if (lt_store->window->egl_surface == EGL_NO_SURFACE)
    {
        emit_error("failed to create egl surface");
        return 0;
    }

    eglMakeCurrent(lt_store->window->egl_display, lt_store->window->egl_surface, lt_store->window->egl_surface, lt_store->window->egl_context);

    if (eglSwapInterval(lt_store->window->egl_display, 1) == EGL_FALSE)
    {
        emit_error("failed to enable vertical sync");
    }

    return 1;
}

static void destroy_egl_surface()
{
    if (lt_store->window->egl_surface != NULL)
        eglDestroySurface(lt_store->window->egl_display, lt_store->window->egl_surface);

    if (lt_store->window->egl_window != NULL)
        wl_egl_window_destroy(lt_store->window->egl_window);

    if (lt_store->window->egl_context != NULL)
        eglDestroyContext(lt_store->window->egl_display, lt_store->window->egl_context);

    if (lt_store->window->egl_display != NULL)
        eglTerminate(lt_store->window->egl_display);
}

static double get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec + (time.tv_usec / 1000000.0);
}

// private header
// ---------------------------------------------------------------- 

int window_create()
{
    lt_store->window = malloc(sizeof(window_store));
    if (lt_store->window == NULL)
    {
        emit_error("failed to allocate internal window store");
        return 0;
    }

    if (!create_wayland_window() || !create_xdg_shell() || !create_egl_surface())
        return 0;

    double now = get_time();
    lt_store->window->time_began = now;
    lt_store->window->last_frame_time = now;
    lt_store->window->cur_frame_time = now;
    lt_store->window->delta_time = 0.0; 

    return 1;
}

void window_destroy()
{
    destroy_egl_surface();
    destroy_xdg_shell();
    destroy_wayland_window();
    
    free(lt_store->window);
    lt_store->window = NULL;
}

void window_poll_events()
{
    lt_store->window->last_frame_time = lt_store->window->cur_frame_time;
    lt_store->window->cur_frame_time = get_time();
    lt_store->window->delta_time = lt_store->window->cur_frame_time - lt_store->window->last_frame_time;

    wl_display_dispatch_pending(lt_store->window->wl_display);
    wl_display_flush(lt_store->window->wl_display);
}

void window_swap_buffers()
{
    eglSwapBuffers(lt_store->window->egl_display, lt_store->window->egl_surface);
}

double window_get_time()
{
    return get_time() - lt_store->window->time_began;
}

double window_get_fps()
{
    if (lt_store->window->delta_time == 0.0)
        return 0;

    return 1.0 / lt_store->window->delta_time;
}

double window_get_delta()
{
    return lt_store->window->delta_time;
}
