#include "lux/render.h"
#include "lux/tools.h"

#include <string.h>
#include <stdlib.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

struct _lx_window
{
    struct wl_display* display;
    struct wl_registry* registry;
    struct wl_compositor* compositor;
    struct wl_shell* shell;
    struct wl_surface* surface;
    struct wl_shell_surface* shell_surface;
};

//
//  private
//

void registry_handler(void* data, struct wl_registry* registry, uint32_t id, const char* interface, uint32_t version)
{
    lx_window* window = data;

    if (strcmp(interface, wl_compositor_interface.name) == 0)
    {
        window->compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    }
    else if (strcmp(interface, wl_shell_interface.name) == 0)
    {
        window->shell = wl_registry_bind(registry, id, &wl_shell_interface, 1);
    }
}

const struct wl_registry_listener registry_listener =
{
    registry_handler,
    NULL
};

//
//  public
//

lx_window* lx_window_new(const char* title, int width, int height)
{
    lx_window* window = malloc(sizeof(lx_window));
    if (!window)
    {
        lx_error("failed to allocate window");
        return NULL;
    }
    lx_debug("allocated window");

    window->display = wl_display_connect(NULL);
    if (!window->display)
    {
        lx_error("failed to connect to wayland display");
        lx_window_delete(window);
        return NULL;
    }
    lx_debug("connected to wayland display");

    window->registry = wl_display_get_registry(window->display);
    wl_registry_add_listener(window->registry, &registry_listener, window);
    wl_display_roundtrip(window->display);

    if (!window->compositor || !window->shell)
    {
        lx_error("failed to find compositor or shell");
        lx_window_delete(window);
        return NULL;
    }

    window->surface = wl_compositor_create_surface(window->compositor);
    window->shell_surface = wl_shell_get_shell_surface(window->shell, window->surface);
    wl_shell_surface_set_toplevel(window->shell_surface);
    
    if (!window->surface || !window->shell_surface)
    {
        lx_error("failed to create a (shell) surface");
        lx_window_delete(window);
        return NULL;
    }

    return window;
}

void lx_window_delete(lx_window* window)
{
    if (window->shell_surface != NULL)
        wl_shell_surface_destroy(window->shell_surface);

    if (window->surface != NULL)
        wl_surface_destroy(window->surface);

    if (window->display != NULL)
        wl_display_disconnect(window->display);

    free(window);
}

void lx_window_update(lx_window* window)
{
}

void lx_window_render(lx_window* window)
{

}

int lx_window_has_received_close_signal(lx_window* window)
{
    return wl_display_dispatch(window->display) == -1;
}
