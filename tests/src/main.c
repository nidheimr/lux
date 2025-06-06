#include "lux/tools.h"
#include <lux.h>

int main()
{
    lx_enable_debug_messages(1);

    lx_window* window = lx_window_create("Lux Window", 1920, 1080); 
    lx_shader shader = lx_shader_create("default.vert", "default.frag");

    while (lx_window_is_alive(window))
    {
        lx_window_update(window);
        
        lx_shader_test(shader);

        lx_window_render(window);
    }

    lx_shader_destroy(shader);
    lx_window_destroy(window);

    return 0;
}
