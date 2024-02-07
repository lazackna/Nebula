#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform sampler2D ourTexture;

void main()
{
    gl_FragColor = vec4(position, 1.f);
}