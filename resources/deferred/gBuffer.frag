#version 400
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 texcoord;
in vec3 position;
in vec3 normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

out vec4 color;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = position;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(normal);
    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(texture_diffuse1, texcoord).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = 1.0f;//texture(texture_specular1, TexCoords).r;

    color = vec4(gAlbedoSpec.rgb, 1.0f);
}

