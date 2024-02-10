#version 400
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

out vec2 texCoord;

void main()
{
    texCoord = a_texcoord;
    gl_Position = vec4(a_position, 1.0);
}