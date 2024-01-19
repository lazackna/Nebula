#version 400
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 position;
out vec3 normal;
out vec2 texcoord;
out vec4 color;

void main()
{
    //normal = normalize(normalMatrix * a_normal);
    position = a_position;
    normal = a_normal;
    texcoord = a_texcoord;
    color = a_color;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_position,1);
}