#include "lux/render.h"
#include <lux.h>

int main()
{
    lx_enable_debug_messages(1);
    lx_window* window = lx_window_new("Lux", 1920, 1080);

    while (lx_window_has_received_close_signal(window))
    {
        lx_window_update(window);
        lx_window_render(window);
    }

    lx_window_delete(window);

    return 0;
}
