#include <lux.h>
#include <stdio.h>

#include "test_gl.h"

static int wireframe = 0;

void on_key_event(lx_keycode key, lx_keystate state)
{
    if (key == LX_KEY_ENTER && state == LX_PRESSED)
        wireframe = !wireframe;
}

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

        .on_key_event = on_key_event,
        .on_resize = on_resize,
        .on_error = on_error,
    });

    create_test_shader();
    create_test_cube();

    while (lx_is_alive())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lx_poll_events();

        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lx_get_key_state(LX_KEY_SPACE) == LX_PRESSED || lx_get_key_state(LX_KEY_SPACE) == LX_REPEATED)
            draw_test_cube();

        lx_swap_buffers();
    }

    lx_quit();
    return 0;
}
