#version 450 core
out vec4 fragcolor;
#define MAX_LIGHTS 16

uniform int lightindex;

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

void main() {
    Light currentlight = lights[lightindex];
    fragcolor = vec4(currentlight.color.xyz * currentlight.intensity, currentlight.color.w);
}

