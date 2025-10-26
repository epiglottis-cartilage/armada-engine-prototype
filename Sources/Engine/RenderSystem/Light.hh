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
    float _pad0[3];

    glm::vec4 position = {0,0,0,0};
    glm::vec4 direction = {0,0,0,0};
    glm::vec4 color = {0,0,0,0};

    float intensity = 1;
    float range = 5;
    float _pad1[2];

    gpuLightStruct() = default;
    //this method is for direction light only
    gpuLightStruct(typeLight type, glm::vec3 direction, glm::vec4 color, float intensity);
    //this method is for point light only
    gpuLightStruct(typeLight type, glm::vec3 position, glm::vec4 color, float intensity, float range);
};

struct alignas(16) LightBuffer {
    int32_t numLights = 0;
    float _pad0[3];
    gpuLightStruct lightInstance[MAX_LIGHTS];
};



NAMESPACE_END

#endif //LIGHT_HH
