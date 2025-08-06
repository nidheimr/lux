#include <lux.h>
#include <stdio.h>

#include "test_gl.h"

void on_resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void on_error(const char* desc)
{
    printf("\033[31merror\033[0m %s\n", desc);
}

int main()
{
    lx_init((lx_init_props){
        .title = "Lux Test",
        .width = 1280,
        .height = 720,

        .on_resize = on_resize,
        .on_error = on_error,
    });

    create_test_shader();
    create_test_cube();

    while (lx_is_alive())
    {
        lx_poll_events();

        draw_test_cube();

        lx_swap_buffers();
    }

    lx_quit();
    return 0;
}
