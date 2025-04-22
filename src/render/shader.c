#include "lux/render.h"
#include "lux/tools.h"
#include "lux/bindings.h"

#define SHADER_PROGRAM 1

//
//  private
//

char error_log[512];

int populate_error_log(unsigned int type, unsigned int target)
{
    int success;

    switch (type)
    {
    case GL_VERTEX_SHADER:
    case GL_FRAGMENT_SHADER:
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if (!success)
            glGetShaderInfoLog(target, 512, NULL, error_log);

        break;

    case SHADER_PROGRAM:
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success)
            glGetProgramInfoLog(target, 512, NULL, error_log);

        break;
    }

    return !success; // inverted because 0 should indicate no problems
}

unsigned int create_shader(unsigned int shader_type, const char* source)
{
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

unsigned int create_program(unsigned int vertex, unsigned int fragment)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

//
//  public
//

lx_shader lx_shader_new(const char* vertex_source, const char* fragment_source)
{
    unsigned int vertex = create_shader(GL_VERTEX_SHADER, vertex_source);
    if (populate_error_log(GL_VERTEX_SHADER, vertex))
    {
        lx_error("vertex shader compilation failed, opengl error: %s", error_log);
        return 0;
    }

    unsigned int fragment = create_shader(GL_FRAGMENT_SHADER, fragment_source);
    if (populate_error_log(GL_FRAGMENT_SHADER, fragment))
    {
        lx_error("fragment shader compilation failed, opengl error: %s", error_log);
        return 0;
    }

    unsigned int program = create_program(vertex, fragment);
    if (populate_error_log(SHADER_PROGRAM, program))
    {
        lx_error("shader program linking failed, opengl error: %s", error_log);
        return 0;
    }

    lx_debug("created shader %u", program);
    return program;
}

void lx_shader_delete(lx_shader shader)
{
    if (!glIsProgram(shader))
    {
        lx_error("tried deleting non-existant shader %u", shader);
        return;
    }

    glDeleteProgram(shader);
    lx_debug("deleted shader %u", shader);
}

void lx_shader_use(lx_shader shader)
{
    glUseProgram(shader);
}