#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform vec4 colorLight;
uniform float flIntensity;
uniform mat4 matrixModel;

layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 matrixView;
    mat4 matrixProjection;
    vec3 positionCamera;
};
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

void main()
{

    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);

}
