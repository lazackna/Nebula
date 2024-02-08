#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform sampler2D albedo;
uniform sampler2D specular;

void main()
{
    vec4 outputColor = vec4(1,1,1,1);
    outputColor.rgb = texture(albedo, texcoord).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    outputColor.a = texture(specular, texcoord).r;

    gl_FragColor = outputColor;
}