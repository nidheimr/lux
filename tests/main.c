#include "lux/output.h"
#include "lux/tools.h"
#include <lux.h>

int main()
{
    lx_enable_debug_messages(1);

    lx_window* window = lx_window_create("Lux Window", 1920, 1080);

    glClearColor(1.0f, 0.82f, 0.86f, 1.0f);

    while (lx_window_is_alive(window))
    {
        lx_window_update(window);
        lx_window_render(window);
    }

    lx_window_destroy(window);

    return 0;
}
