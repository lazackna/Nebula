#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform bool useTexture;

struct PointLight {
    vec3 position;

    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTex;
    sampler2D normalTex;
};

uniform Material material;
uniform PointLight pointLight;

out vec4 fragColor;

vec4 calculateDiffuseColor() {
    vec3 lightDir = normalize(pointLight.position - position);

    float diffuseFactor = max(0,dot(lightDir, normalize(normal)));
    vec4 diffuseColor = vec4(0,0,0,0);

    if(diffuseFactor > 0){
        diffuseColor = vec4(pointLight.color, 1.0f) *
        pointLight.diffuseIntensity *
        diffuseFactor;
    }
    return diffuseColor;
}

void main()
{
    vec4 outputColor = vec4(1.f,1.f,1.f,1.f);

    if(useTexture) {
        outputColor *= texture2D(material.diffuseTex, texcoord);
    } else {
        outputColor *= color;
    }

    vec4 ambientColor = vec4(1.f,1.f,1.f,1.f);
    vec4 diffuseColor = vec4(0.f,0.f,0.f,0.f);

    ambientColor *= vec4(pointLight.color, 1.f) * pointLight.ambientIntensity;
    diffuseColor = calculateDiffuseColor();

    fragColor = outputColor * (ambientColor + diffuseColor);
}