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
        produce_error("failed to create shader, opengl produced error: %s", info);
        return 0;
    }

    return shader;
}

//
//  public
//

unsigned int lx_shader_create(lx_shader_properties properties)
{
    PARAM_GUARD(lx_glCreateProgram == NULL, ("tried to create a shader before opengl functions were loaded"), 0);
    PARAM_GUARD(properties.vertex_file == NULL, ("could not create shader with a null vertex file"), 0);
    PARAM_GUARD(properties.fragment_file == NULL, ("could not create shader with a null fragment file"), 0);
 
    produce_debug("creating shader from %s and %s", properties.vertex_file, properties.fragment_file);

    unsigned int vert = create_shader_from_file(GL_VERTEX_SHADER, properties.vertex_file);
    if (vert == 0)
        return 0;

    produce_debug("-> created vertex shader");

    unsigned int frag = create_shader_from_file(GL_FRAGMENT_SHADER, properties.fragment_file);
    if (frag == 0)
        return 0;

    produce_debug("-> created fragment shader");
    
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
        produce_error("failed to create program, opengl produced error: %s", info);
        
        glDeleteShader(vert);
        glDeleteShader(frag);
        
        return 0;
    }

    produce_debug("-> created shader program");

    glDeleteShader(vert);
    glDeleteShader(frag);

    produce_debug("finished creating shader");
    return program;
}

void lx_shader_destroy(unsigned int shader)
{
    PARAM_GUARD(lx_glDeleteProgram == NULL, ("tried to destroy a shader before opengl functions were loaded"));
    PARAM_GUARD(glIsProgram(shader) == 0, ("tried to destroy a shader with an invalid id"));

    produce_debug("destroying shader with id %d", shader);

    glDeleteProgram(shader);

    produce_debug("finished destroying shader");
}
