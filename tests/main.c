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

    int draw = 1;
    while (lx_is_alive())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lx_poll_events();

        printf("mouse x,y: %lf,%lf\n", lx_get_mouse_pos().x, lx_get_mouse_pos().y);

        if (lx_get_key_state(LX_KEY_SPACE) == LX_PRESSED)
            draw = !draw;
        
        if (lx_get_key_state(LX_MOUSE_LEFT) == LX_PRESSED)
            draw = !draw;

        if (draw)
            draw_test_cube();

        lx_swap_buffers();
    }

    lx_quit();
    return 0;
}
