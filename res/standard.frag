#version 330 core

in vec3 d_col;

out vec4 FragColor;

void main()
{
    FragColor = vec4(d_col.x, d_col.y, d_col.z, 1.0f);
}