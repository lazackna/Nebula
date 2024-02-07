#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform sampler2D ourTexture;

void main()
{
    vec4 outputColor = vec4(1.f,1.f,1.f,1.f);

    outputColor *= texture2D(ourTexture, texcoord);

    gl_FragColor = color;
}