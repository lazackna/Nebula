#version 400

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

uniform sampler2D albedo;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

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
    vec3 lightColor = lightColor;
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - position);
    float diff = max(dot(norm, lightDir), 0.0);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - position);
    vec3 lighting = texture(albedo, texcoord).rgb * 0.1;
    for(int i = 0; i < NR_LIGHTS; ++i) {
        vec3 diffuse = diff * lights[i].Color;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;
        lighting += specular + diff;
    }

//    vec3 result = (ambient + diffuse + specular) * texture2D(albedo, texcoord).rgb;
    vec3 result = lighting + ambient;
    FragColor = vec4(result, 1.0);
}