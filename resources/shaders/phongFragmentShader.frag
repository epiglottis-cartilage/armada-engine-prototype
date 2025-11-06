#version 450 core

#define MAX_LIGHTS 16

struct Light {
    int type;           //0 + 4
    float intensity;    //4 + 4
    float range;        //8 +4
    int _pad0;          //12 +4
    vec4 position;      //16 +16
    vec4 direction;     //32 +16
    vec4 color;         //48 +16
};//total: 64 bytes per struct

layout(std140, binding = 1) uniform LightBuffer {
    int numLights; //0 + 4
    //rule of struct align: align is the  multiple of its largest member, rounded up to 4N
    float _pad1; //4 + 4
    float _pad2; //8 + 4
    float _pad3; //12 + 4
    Light lights[MAX_LIGHTS]; //16 + 64 * MAX_LIGHTS
};


in VS_OUT {
    vec3 fragPos;
    vec2 TexCoord;
    mat3 TBN;
} fs_in;

out vec4 colorFrag;

uniform sampler2D textureBaseColor;
uniform sampler2D textureRoughness;
uniform sampler2D textureMetalic;
uniform sampler2D textureNormalMap;
uniform sampler2D textureAmbientOcclusion;
uniform mat4 matrixModel;

//transform to camera , to screen
layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 matrixView;
    mat4 matrixProjection;
    vec3 positionCamera;
};

//receive raw, untransformed position
vec3 CalcDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(vec3(light.direction));
    float diff = max(dot(normal, lightDir), 0.0);

    // 简单 Blinn-Phong 高光
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 64.0);

    vec3 ambient = 0.05 * albedo;
    vec3 diffuse = diff * albedo * vec3(light.color) * light.intensity;
    vec3 specular = spec * vec3(light.color) * 0.5;

    return (ambient + diffuse + specular);
}

//this is blinn-phong, since we  are using halfway vector of view and light to dot multiply with normal
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
//transform light position to world
    vec3 positionLightWorld = vec3(light.position * matrixModel);
    vec3 lightDir = normalize(positionLightWorld - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 64.0);

    // 距离衰减
    float distance = length(positionLightWorld - fragPos);
    float attenuation = clamp(1.0 - distance / light.range, 0.0, 1.0);

    vec3 ambient = 0.05 * albedo;
    vec3 diffuse = diff * albedo * vec3(light.color) * light.intensity * attenuation;
    vec3 specular = spec * vec3(light.color) * 0.5 * attenuation;

    return (ambient + diffuse + specular);
}



void main()
{
    vec3 albedo = texture(textureBaseColor, fs_in.TexCoord).rgb;
    vec3 norm = texture(textureNormalMap, fs_in.TexCoord).rgb;
    norm = norm * 2.0 - 1.0;
    norm = normalize(fs_in.TBN * norm);
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









