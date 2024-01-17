#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;

in vec3 position;
in vec4 color;
in vec2 texCoord;
in vec3 normal;

void main()
{
    FragColor = ourColor;
}