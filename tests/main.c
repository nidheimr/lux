#include "lux.h"

const char* vertex_source = "#version 330 core      \n\
layout (location = 0) in vec3 pos;                  \n\
void main()                                         \n\
{                                                   \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);  \n\
}";

const char* fragment_source = "#version 330 core    \n\
out vec4 FragColor;                                 \n\
void main()                                         \n\
{                                                   \n\
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);       \n\
}";

int main()
{
    lx_enable_debug_messages(1);
    
    lx_window* window = lx_window_new("Lux", 1920, 1080);
    lx_shader shader = lx_shader_new(vertex_source, fragment_source);
    
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!lx_window_has_received_quit_signal(window))
    {
        lx_window_update(window);
        lx_shader_use(shader);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        lx_window_render(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    lx_shader_delete(shader);
    lx_window_delete(window);

    return 0;
}
