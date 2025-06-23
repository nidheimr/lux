#include "lux/gl.h"
#include "lux/output.h"
#include "lux/tools.h"

#include "../tools/debug.h"

//
//  private
//

static unsigned int create_shader_from_file(unsigned int type, const char* file)
{
    const char* source = lx_read_file(file);
    if (source == NULL)
        return 0;

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info);
        lx_set_last_error("failed to create shader, opengl produced error: %s", info);
        return 0;
    }

    return shader;
}

//
//  public
//

lx_shader lx_shader_create(const char* vertex_file, const char* fragment_file)
{
    PARAM_GUARD(lx_glCreateProgram == NULL, ("tried to create a shader before opengl functions were loaded"), 0);
    PARAM_GUARD(vertex_file == NULL, ("could not create shader with a null vertex file"), 0);
    PARAM_GUARD(fragment_file == NULL, ("could not create shader with a null fragment file"), 0);
   
    unsigned int vert = create_shader_from_file(GL_VERTEX_SHADER, vertex_file);
    if (vert == 0)
        return 0;

    unsigned int frag = create_shader_from_file(GL_FRAGMENT_SHADER, fragment_file);
    if (frag == 0)
        return 0;

    unsigned int program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    int success;
    char info[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, info);
        lx_set_last_error("failed to create program, opengl produced error: %s", info);
        
        glDeleteShader(vert);
        glDeleteShader(frag);
        return 0;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    lx_debug("created shader with id %d from %s and %s", program, vertex_file, fragment_file);
    return program;
}

void lx_shader_destroy(lx_shader shader)
{
    PARAM_GUARD(lx_glDeleteProgram == NULL, ("tried to destroy a shader before opengl functions were loaded"));
    PARAM_GUARD(glIsProgram(shader) == 0, ("tried to destroy a shader with an invalid id"));

    glDeleteProgram(shader);
    lx_debug("destroyed shader with id %d", shader);
}

void lx_shader_use(lx_shader shader)
{
    PARAM_GUARD(lx_glUseProgram == NULL, ("tried to use a shader before opengl functions were loaded"));
    PARAM_GUARD(glIsProgram(shader) == 0, ("tried to use a shader with an invalid id"));

    glUseProgram(shader);
}

void lx_shader_test(lx_shader shader)
{
    PARAM_GUARD(lx_glGenVertexArrays == NULL, ("tried to test a shader before opengl functions were loaded"));
    PARAM_GUARD(glIsProgram(shader) == 0, ("tried to test a shader with an invalid id"));

    static unsigned int vao = 0;
    static float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    if (vao == 0)
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        lx_debug("created triangle vao for shader testing");
    }

    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
