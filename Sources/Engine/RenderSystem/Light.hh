//
// Created by phage on 10/24/25.
//

#ifndef LIGHT_HH
#define LIGHT_HH

#include <Common.hh>
#include <Model.hh>

NAMESPACE_BEGIN

#define MAX_LIGHTS 16

//some shader uniform name marco, need to find out if reflect is available for this
#define COLORLIGHT "colorLight"
#define FLINTENSITY "flIntensity"

enum class typeLight {
    Directional = 0,
    Point
};

struct alignas(16) gpuLightStruct {
    int type = 0;
    float intensity = 0.7;
    float range = 7;
    float _pad0 = 7;
    glm::vec4 position = {0,0,0,0};
    glm::vec4 direction = {0,0,0,0};
    glm::vec4 color = {0,0,0,0};


    gpuLightStruct() = default;
    gpuLightStruct(typeLight type, glm::vec3 position, glm::vec4 color, float intensity, float range);
};

struct alignas(16) LightBuffer {
    int numLights = 0;
    float _pad0;
    float _pad1;
    float _pad2;
    gpuLightStruct lightInstance[MAX_LIGHTS];
};



NAMESPACE_END

#endif //LIGHT_HH
