#include "lux/output.h"
#include "lux/tools.h"
#include "lux/gl.h"

#include "../platform/xdg_linux.h"
#include "../platform/xdg_deco_linux.h"
#include "../gl/loader.h"
#include "../tools/debug.h"
#include "../input/querying.h"

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <wayland-client-core.h>
#include <wayland-client.h>
#include <wayland-egl.h>

//
//  private - definitions
//

typedef struct _lx_window
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
    struct zxdg_decoration_manager_v1* xdg_deco;

    // egl surface
    EGLDisplay* egl_display;
    EGLContext* egl_context;
    struct wl_egl_window* egl_window;
    EGLSurface* egl_surface;

    // wayland input
    struct wl_seat* wl_seat;
    struct wl_keyboard* wl_keyboard;
    struct wl_pointer* wl_pointer;

    // static properties
    char title[32];
    int width;
    int height;
    lx_window_resize_callback on_resize;

    // dynamic properties
    int is_alive;
    double time_began;
    double last_frame_time;
    double cur_frame_time;
    double delta_time;
}
lx_window;

static lx_window* internal_ref = NULL;
static int xdg_ack = 0;

//
//  private - callbacks
//

// necessary forward declare
static struct wl_keyboard_listener wl_listener_keyboard;
static struct wl_pointer_listener wl_listener_pointer;

static void wl_registry_global(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version)
{
    lx_window* window = data;

    if (strcmp(interface, wl_compositor_interface.name) == 0)
        window->wl_compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);

    if (strcmp(interface, xdg_wm_base_interface.name) == 0)
        window->xdg_wm_base = wl_registry_bind(registry, name, &xdg_wm_base_interface, version);

    if (strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0)
        window->xdg_deco = wl_registry_bind(registry, name, &zxdg_decoration_manager_v1_interface, version);
            
    if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        window->wl_seat = wl_registry_bind(registry, name, &wl_seat_interface, version);
        
        window->wl_keyboard = wl_seat_get_keyboard(window->wl_seat);
        wl_keyboard_add_listener(window->wl_keyboard, &wl_listener_keyboard, NULL);

        window->wl_pointer = wl_seat_get_pointer(window->wl_seat);
        wl_pointer_add_listener(window->wl_pointer, &wl_listener_pointer, NULL);
    }
}

static void wl_registry_global_remove(void* data, struct wl_registry* registry, uint32_t name)
{}

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
    lx_window* window = data;
    window->is_alive = 0;
}

static void xdg_toplevel_configure(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height, struct wl_array* states)
{
    if (width <= 0 || height <= 0)
        return;

    lx_window* window = data;
    window->width = width;
    window->height = height;

    wl_egl_window_resize(window->egl_window, width, height, 0, 0);

    if (window->on_resize == NULL)
        glViewport(0, 0, width, height);
    else
        window->on_resize(window, width, height);
}

static void xdg_toplevel_configure_bounds(void* data, struct xdg_toplevel* toplevel, int32_t width, int32_t height)
{}

static void xdg_toplevel_wm_capabilities(void* data, struct xdg_toplevel* toplevel, struct wl_array* capabilities)
{}

static void wl_keyboard_keymap(void* data, struct wl_keyboard* kb, uint32_t format, int fd, uint32_t size)
{
    close(fd);
}

static void wl_keyboard_key(void* data, struct wl_keyboard* kb, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
    inp_update_key(key, state);
}

static void wl_keyboard_repeat_info(void* data, struct wl_keyboard* kb, int32_t rate, int32_t delay)
{}

static void wl_keyboard_enter(void* data, struct wl_keyboard* kb, uint32_t serial, struct wl_surface* surface, struct wl_array* keys)
{}

static void wl_keyboard_leave(void* data, struct wl_keyboard* kb, uint32_t serial, struct wl_surface* surface)
{}

static void wl_keyboard_modifiers(void* data, struct wl_keyboard* kb, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{}

static void wl_pointer_motion(void* data, struct wl_pointer* ptr, uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    inp_update_mouse_pos(wl_fixed_to_double(sx), wl_fixed_to_double(sy));
}

static void wl_pointer_button(void* data, struct wl_pointer* ptr, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
    inp_update_mouse_button(button, state);
}

static void wl_pointer_axis(void* data, struct wl_pointer* ptr, uint32_t time, uint32_t axis, wl_fixed_t value)
{}

static void wl_pointer_axis_discrete(void* data, struct wl_pointer* ptr, uint32_t axis, int32_t discrete)
{}

static void wl_pointer_axis_relative_direction(void* data, struct wl_pointer* ptr, uint32_t axis, uint32_t direction)
{}

static void wl_pointer_axis_source(void* data, struct wl_pointer* ptr, uint32_t source)
{}

static void wl_pointer_axis_stop(void* data, struct wl_pointer* ptr, uint32_t time, uint32_t axis)
{}

static void wl_pointer_axis_value120(void* data, struct wl_pointer* ptr, uint32_t axis, int32_t value120)
{}

static void wl_pointer_enter(void* data, struct wl_pointer* ptr, uint32_t serial, struct wl_surface* surface, wl_fixed_t sx, wl_fixed_t sy)
{}

static void wl_pointer_leave(void* data, struct wl_pointer* ptr, uint32_t serial, struct wl_surface* surface)
{}

static void wl_pointer_frame(void* data, struct wl_pointer* ptr)
{}

//
//  private - listeners
//

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

static struct wl_keyboard_listener wl_listener_keyboard =
{
    .keymap = wl_keyboard_keymap,
    .key = wl_keyboard_key,
    .repeat_info = wl_keyboard_repeat_info, 
    .enter = wl_keyboard_enter,
    .leave = wl_keyboard_leave, 
    .modifiers = wl_keyboard_modifiers
};

static struct wl_pointer_listener wl_listener_pointer =
{
    .motion = wl_pointer_motion,
    .button = wl_pointer_button,
    .axis = wl_pointer_axis,
    .axis_discrete = wl_pointer_axis_discrete,
    .axis_relative_direction = wl_pointer_axis_relative_direction,
    .axis_source = wl_pointer_axis_source,
    .axis_stop = wl_pointer_axis_stop,
    .axis_value120 = wl_pointer_axis_value120,
    .enter = wl_pointer_enter,
    .leave = wl_pointer_leave,
    .frame = wl_pointer_frame 
};

//
//  private
//

static const char* create_wayland_window(lx_window* window)
{
    window->wl_display = wl_display_connect(NULL);
    if (!window->wl_display)
        return "failed to connect to wayland display";

    lx_produce_debug("-> created wl display");

    window->wl_registry = wl_display_get_registry(window->wl_display);
    if (!window->wl_registry)
        return "failed to get wayland display registry";

    wl_registry_add_listener(window->wl_registry, &wl_listener_registry, window);
    lx_produce_debug("-> created wl registry");
    
    if (wl_display_roundtrip(window->wl_display) < 0)
        return "failed to complete wayland round trip";

    if (!window->wl_compositor) // set by wl_display_roundtrip and the registry_global callback
        return "failed to get wayland compositor";

    lx_produce_debug("-> created wl compositor");

    window->wl_surface = wl_compositor_create_surface(window->wl_compositor);
    if (!window->wl_surface)
        return "failed to create wayland surface";

    lx_produce_debug("-> created wl surface");

    return NULL;
}

static void destroy_wayland_window(lx_window* window)
{
    if (window->wl_surface != NULL)
    {
        wl_surface_destroy(window->wl_surface);
        lx_produce_debug("-> destroyed wl surface");
    }

    if (window->wl_compositor != NULL)
    {
        wl_compositor_destroy(window->wl_compositor);
        lx_produce_debug("-> destroyed wl compositor");
    }

    if (window->wl_registry != NULL)
    {
        wl_registry_destroy(window->wl_registry);
        lx_produce_debug("-> destroyed wl registry");
    }

    if (window->wl_display != NULL)
    {
        wl_display_disconnect(window->wl_display);
        lx_produce_debug("-> destroyed wl display");
    }
}

static const char* create_xdg_shell(lx_window* window)
{
    if (!window->xdg_wm_base) // set by wl_display_roundtrip and the registry_global callback
        return "failed to get xdg wm base";

    xdg_wm_base_add_listener(window->xdg_wm_base, &xdg_listener_wm_base, NULL);
    lx_produce_debug("-> created xdg wm base");

    window->xdg_surface = xdg_wm_base_get_xdg_surface(window->xdg_wm_base, window->wl_surface);
    if (!window->xdg_surface)
        return "failed to create xdg surface";

    xdg_surface_add_listener(window->xdg_surface, &xdg_listener_surface, NULL);
    lx_produce_debug("-> created xdg surface");

    window->xdg_toplevel = xdg_surface_get_toplevel(window->xdg_surface);
    if (!window->xdg_toplevel)
        return "failed to create xdg toplevel";

    xdg_toplevel_set_title(window->xdg_toplevel, window->title);
    xdg_toplevel_set_app_id(window->xdg_toplevel, window->title);
    xdg_toplevel_add_listener(window->xdg_toplevel, &xdg_listener_toplevel, window);

    lx_produce_debug("-> created xdg toplevel");

    // only if ssd are available, use them
    if (window->xdg_deco) // set by wl_display_roundtrip and the registry_global callback
    {
        struct zxdg_toplevel_decoration_v1* deco = zxdg_decoration_manager_v1_get_toplevel_decoration(window->xdg_deco, window->xdg_toplevel); 
        zxdg_toplevel_decoration_v1_set_mode(deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);

        lx_produce_debug("-> created and using server side decorations");
    }
    else
        lx_produce_debug("-> server side decorations unavailable, defaulting to client side decoration");

    // wait until xdg acks, otherwise it will error
    wl_surface_commit(window->wl_surface);
    while (xdg_ack == 0)
        wl_display_dispatch(window->wl_display);
     
    return NULL;
}

static void destroy_xdg_shell(lx_window* window)
{
    if (window->xdg_toplevel != NULL)
    {
        xdg_toplevel_destroy(window->xdg_toplevel);
        lx_produce_debug("-> destroyed xdg toplevel");
    }

    if (window->xdg_surface != NULL)
    {
        xdg_surface_destroy(window->xdg_surface);
        lx_produce_debug("-> destroyed xdg surface");
    }

    if (window->xdg_wm_base != NULL)
    {
        xdg_wm_base_destroy(window->xdg_wm_base);
        lx_produce_debug("-> destroyed xdg wm base");
    }
}

static const char* create_egl_surface(lx_window* window)
{
    window->egl_display = eglGetDisplay((EGLNativeDisplayType)window->wl_display); 
    if (window->egl_display == EGL_NO_DISPLAY)
        return "failed to create egl display";

    lx_produce_debug("-> created egl display");
    
    if (eglInitialize(window->egl_display, NULL, NULL) != EGL_TRUE)
        return "failed to initialise egl";

    lx_produce_debug("-> initialised egl");

    EGLConfig config;
    EGLint num_configs;
    EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    if (eglChooseConfig(window->egl_display, attribs, &config, 1, &num_configs) != EGL_TRUE)
        return "failed to choose egl config";

    EGLint context_attribs[] = { EGL_NONE };
    eglBindAPI(EGL_OPENGL_API);
    
    lx_produce_debug("-> configured egl");

    window->egl_context = eglCreateContext(window->egl_display, config, EGL_NO_CONTEXT, context_attribs);
    if (!window->egl_context)
        return "failed to create egl context";

    lx_produce_debug("-> created egl context");

    window->egl_window = wl_egl_window_create(window->wl_surface, window->width, window->height);
    if (!window->egl_window)
        return "failed to create egl window";

    lx_produce_debug("-> created egl window"); 

    window->egl_surface = eglCreateWindowSurface(window->egl_display, config, (EGLNativeWindowType)window->egl_window, NULL);
    if (window->egl_surface == EGL_NO_SURFACE)
        return "failed to create egl surface";

    lx_produce_debug("-> created egl surface");

    return NULL;
}

static void destroy_egl_surface(lx_window* window)
{
    if (window->egl_surface != NULL)
    {
        eglDestroySurface(window->egl_display, window->egl_surface);
        lx_produce_debug("-> destroyed egl surface");
    }

    if (window->egl_window != NULL)
    {
        wl_egl_window_destroy(window->egl_window);
        lx_produce_debug("-> destroyed egl window");
    }

    if (window->egl_context != NULL)
    {
        eglDestroyContext(window->egl_display, window->egl_context);
        lx_produce_debug("-> destroyed egl context");
    }

    if (window->egl_display != NULL)
    {
        eglTerminate(window->egl_display);
        lx_produce_debug("-> destroyed egl display");
    }
}

static double get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec + (time.tv_usec / 1000000.0);
}

//
//  public
//

lx_window* lx_window_create(lx_window_properties properties)
{
    PARAM_GUARD(internal_ref != NULL, ("could not create another window when one already exists as multiple windows are not supported"), NULL);
    PARAM_GUARD(properties.title == NULL, ("could not create window with null title"), NULL);
    PARAM_GUARD(properties.width < 1 || properties.width > 7680 || properties.height < 1 || properties.height > 4320, ("could not create window with improper dimensions, expected 1x1 to 7680x4320 but got %dx%d", properties.width, properties.height), NULL);

    lx_produce_debug("creating window %s @ %dx%d", properties.title, properties.width, properties.height);

    lx_window* window = malloc(sizeof(lx_window));
    if (!window)
    {
        lx_produce_error("failed to allocate window struct");
        return NULL;
    }
    lx_produce_debug("-> allocated window struct");

    snprintf(window->title, sizeof(window->title), "%s", properties.title);
    window->width = properties.width;
    window->height = properties.height;
    window->on_resize = properties.on_resize;

    window->is_alive = 1;

    double now = get_time();
    window->time_began = now;
    window->last_frame_time = now;
    window->cur_frame_time = now;
    window->delta_time = 0.0;

    const char* success = create_wayland_window(window);
    if (success != NULL)
    {
        lx_produce_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    success = create_xdg_shell(window);
    if (success != NULL)
    {
        lx_produce_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    success = create_egl_surface(window);
    if (success != NULL)
    {
        lx_produce_error("%s", success);
        lx_window_destroy(window);
        return NULL;
    }

    eglMakeCurrent(window->egl_display, window->egl_surface, window->egl_surface, window->egl_context); 
    lx_produce_debug("-> made window current");

    int version = load_gl_procs();
    version = load_gl_procs();
    if (version == 0)
    {
        lx_window_destroy(window);
        return NULL;
    }
    lx_produce_debug("-> loaded opengl version %d.%d", (version / 10000), (version % 10000));

    lx_produce_debug("finished creating window");

    internal_ref = window;
    return window;
}

void lx_window_destroy(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not destroy null window"));

    lx_produce_debug("destroying window %s", window->title);

    destroy_egl_surface(window);
    destroy_xdg_shell(window);
    destroy_wayland_window(window);

    free(window);
    lx_produce_debug("-> freed window struct");
    
    internal_ref = NULL;
    lx_produce_debug("finished destroying window");
}

const char* lx_window_get_title(lx_window* window)
{
    return window->title;
}

int lx_window_get_width(lx_window* window)
{
    return window->width;
}

int lx_window_get_height(lx_window* window)
{
    return window->height;
}

double lx_window_get_delta_time(lx_window* window)
{
    return window->delta_time;
}

int lx_window_get_fps(lx_window* window)
{
    if (window->delta_time == 0.0)
        return 0;

    return (int)(1.0 / window->delta_time);
}

double lx_window_get_time_elapsed(lx_window* window)
{
    return get_time() - window->time_began;
}

void lx_window_update(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not update null window"));
    
    window->last_frame_time = window->cur_frame_time;
    window->cur_frame_time = get_time();
    window->delta_time = window->cur_frame_time - window->last_frame_time;

    wl_display_dispatch_pending(window->wl_display);
    wl_display_flush(window->wl_display);
}

void lx_window_swap_buffers(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not render null window"));
    eglSwapBuffers(window->egl_display, window->egl_surface);
}

int lx_window_is_alive(lx_window* window)
{
    PARAM_GUARD(window == NULL, ("could not determine alive state of null window"), 0);
    return window->is_alive;
}
