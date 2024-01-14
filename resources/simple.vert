#version 400
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec3 a_normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 normal;

void main()
{
    normal = normalMatrix * a_normal;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_position,1);
}