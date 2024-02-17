#version 330 core

#define TILE_SHININESS 32

out vec4 FragColor;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight light;
uniform DirLight dirLight;

#define MAX_LIGHTS 128
uniform int size;
uniform PointLight pointLights[MAX_LIGHTS];

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex;
uniform vec3 camPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseVec, vec3 specVec)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), TILE_SHININESS);
    // combine results
    vec3 ambient  = light.ambient  * diffuseVec;
    vec3 diffuse  = light.diffuse  * diff * diffuseVec;
    vec3 specular = light.specular * spec * specVec;
    return (diffuse + ambient + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseVec, vec3 specVec)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), TILE_SHININESS);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient  * diffuseVec;
    vec3 diffuse  = light.diffuse  * diffuseVec;
    vec3 specular = light.specular * spec * specVec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    // get vectors
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);

    // get textures
    vec3 diffuseVec = vec3(texture(tex, TexCoords));
    vec3 specVec = vec3(1.0f);

    // calculate lights
    vec3 directionLight = CalcDirLight(dirLight, norm, viewDir, diffuseVec, specVec);
    vec3 pointLight = vec3(0,0,0);
    for (int i = 0; i < size; i++) {
        pointLight += CalcPointLight(pointLights[i], norm, FragPos, viewDir, diffuseVec, specVec);
    }

    // return color
    FragColor = vec4(directionLight + pointLight, 1.0);
}