#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D positionTex;
uniform sampler2D normalTex;
uniform sampler2D albedoTex;

uniform vec3 cameraPos;

struct Light {
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
    float Radius;
};
const int NR_LIGHTS = 1;
uniform Light lights[NR_LIGHTS];

void main()
{
    vec3 FragPos = texture(positionTex, texCoord).rgb;
    vec3 Normal = texture(normalTex, texCoord).rgb;
    vec3 Diffuse = texture(albedoTex, texCoord).rgb;
    float Specular = texture(albedoTex, texCoord).a;

    vec3 lighting = Diffuse * 0.1;
    vec3 viewDir = normalize(cameraPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i) {
        float distance = length(lights[i].Position - FragPos);
        if(distance >= lights[i].Radius) {
            continue;
        }

        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
        // specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0);
        vec3 specular = lights[i].Color * spec * 0.5;
        // attenuation
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;
    }
    //lighting += vec3(0.5, 0.5, 0.5);
    FragColor = vec4(lighting, 1.0);
}

