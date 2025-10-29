#version 450 core
out vec4 fragcolor;
#define MAX_LIGHTS 16

uniform int lightindex;

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

void main() {
    fragcolor = lights[lightindex].color * lights[lightindex].intensity;
}

