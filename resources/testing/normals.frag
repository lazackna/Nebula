#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform sampler2D ourTexture;

void main()
{
    vec3 outputColor = normal;
    outputColor = outputColor + 0.5f;
    gl_FragColor = vec4(outputColor, 1.0f);
}