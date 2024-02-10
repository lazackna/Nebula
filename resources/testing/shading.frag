#version 400
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D positionTex;
uniform sampler2D normalTex;
uniform sampler2D albedoTex;

//uniform vec3 cameraPos;
//
//struct Light {
//    vec3 Position;
//    vec3 Color;
//
//    float Linear;
//    float Quadratic;
//    float Radius;
//};
//const int NR_LIGHTS = 32;
//uniform Light lights[NR_LIGHTS];

void main()
{
    vec3 FragPos = texture(positionTex, texCoord).rgb;
    vec3 Normal = texture(normalTex, texCoord).rgb;
    vec3 Diffuse = texture(albedoTex, texCoord).rgb;
    float Specular = texture(albedoTex, texCoord).a;

    vec3 lighting = Diffuse * 0.1;
//    vec3 viewDir = normalize(cameraPos - FragPos);
//
//    for(int i = 0; i < NR_LIGHTS; ++i) {
//
//    }

    FragColor = vec4(lighting, 1.0);
}

