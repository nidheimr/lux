#version 330 core

layout (location = 0) in vec3 aloc;

void main()
{
    gl_Position = vec4(aloc, 1.0);
}
