//
// Created by phage on 10/24/25.
//

#include "Light.hh"

NAMESPACE_BEGIN


gpuLightStruct::gpuLightStruct(typeLight type, glm::vec3 direction, glm::vec4 color, float intensity) {
    if (type != typeLight::Directional)
        ENGINE_WARN("You are creating a directional light with a non-directional type in your params, are you sure?");
    this->type = 0;
    this->direction = glm::vec4(direction, 1.0);
    this->color = color;
    this->intensity = intensity;
}

gpuLightStruct::gpuLightStruct(typeLight type, glm::vec3 position, glm::vec4 color, float intensity, float range) {
    if (type != typeLight::Point)
        ENGINE_WARN("You are creating a point light with a non-point light type in your params, are you sure?");
    this->type = 1;
    this->position = glm::vec4(position, 1.0);
    this->color = color;
    this->intensity = intensity;
    this->range = range;
}
NAMESPACE_END