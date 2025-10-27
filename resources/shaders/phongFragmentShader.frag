#version 450 core

#define MAX_LIGHTS 16

struct Light {
    int type;
    vec3 _pad0;
    vec4 position;
    vec4 direction;
    vec4 color;
    float intensity;
    float range;
    vec2 _pad1;
};

layout(std140, binding = 1) uniform LightBuffer {
    int numLights;
    vec3 _padglobal;
    Light lights[MAX_LIGHTS];
};

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 TexCoord;
} fs_in;

out vec4 colorFrag;
uniform sampler2D textureBaseColor;

//transform to camera , to screen
layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 matrixView;
    mat4 matrixProjection;
    vec3 positionCamera;
};

vec3 CalcDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(-vec3(light.direction));
    float diff = max(dot(normal, lightDir), 0.0);

    // 简单 Blinn-Phong 高光
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 64.0);

    vec3 ambient = 0.05 * albedo;
    vec3 diffuse = diff * albedo * vec3(light.color) * light.intensity;
    vec3 specular = spec * vec3(light.color) * 0.5;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 64.0);

    // 距离衰减
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = clamp(1.0 - distance / light.range, 0.0, 1.0);

    vec3 ambient = 0.05 * albedo;
    vec3 diffuse = diff * albedo * vec3(light.color) * light.intensity * attenuation;
    vec3 specular = spec * vec3(light.color) * 0.5 * attenuation;

    return (ambient + diffuse + specular);
}



void main()
{
    vec3 albedo = texture(textureBaseColor, fs_in.TexCoord).rgb;
    vec3 norm = normalize(fs_in.normal);
    vec3 viewDir = normalize(positionCamera - fs_in.fragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        if (lights[i].type == 0)
            result += CalcDirectionalLight(lights[i], norm, viewDir, albedo);
        else if (lights[i].type == 1)
            result += CalcPointLight(lights[i], norm, fs_in.fragPos, viewDir, albedo);
    }

    colorFrag = vec4(result, 1.0);
}









