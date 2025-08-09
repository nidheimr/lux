#include "test_gl.h"

#include <lux.h>

static unsigned int shader;
static unsigned int vao;

void create_test_shader()
{
    if (glUseProgram == NULL) return;

    static const char* vertex =
        "#version 330 core\n"
        "layout (location = 0) in vec3 vpos;\n"
        "layout (location = 1) in vec3 vcol;\n"
        "out vec3 fcol;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "void main(){\n"
        "   gl_Position = projection * view * model * vec4(vpos, 1.0f);\n"
        "   fcol = vcol;\n"
        "}";

    static const char* fragment =
        "#version 330 core\n"
        "in vec3 fcol;\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(fcol, 1.0f);\n"
        "}";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex, NULL);
    glCompileShader(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment, NULL);
    glCompileShader(fs);

    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(shader); 
}

void create_test_cube()
{
    if (glUseProgram == NULL) return;
    
    static const float vertices[] =
    {
        -1,-1,-1, 1,0,0,
         1,-1,-1, 0,1,0,
         1, 1,-1, 0,0,1,
        -1, 1,-1, 1,1,0,
        -1,-1, 1, 1,0,1,
         1,-1, 1, 0,1,1,
         1, 1, 1, 1,1,1,
        -1, 1, 1, 1,0,1
    };

    static const unsigned int indices[] =
    {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,4,7, 7,3,0,
        1,5,6, 6,2,1,
        3,2,6, 6,7,3,
        0,1,5, 5,4,0
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void draw_test_cube()
{
    if (glUseProgram == NULL) return;

    glUseProgram(shader); 

    lx_mat4 perspective = lx_mat4_perspective(45.0f, (float)lx_get_width()/(float)lx_get_height(), 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, perspective.m);

    lx_mat4 view = lx_mat4_identity();
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, view.m);

    lx_mat4 model = lx_mat4_identity();
    model = lx_mat4_translate(model, (lx_vec3){ 0.0f, 0.0f, -5.0f });
    model = lx_mat4_rotate(model, (lx_vec3){ 0.0f, 1.0f, 0.0f }, 45.0f * lx_get_time());
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model.m);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
