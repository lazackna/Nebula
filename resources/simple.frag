#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

in vec3 normalColor;
uniform sampler2D ourTexture;

void main()
{
    gl_FragColor = texture(ourTexture, texcoord);
}