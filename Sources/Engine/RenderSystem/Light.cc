//
// Created by phage on 10/24/25.
//

#include "Light.hh"

NAMESPACE_BEGIN



gpuLightStruct::gpuLightStruct(typeLight type, glm::vec3 position, glm::vec4 color, float intensity, float range) {
//    if (type != typeLight::Point)
//        ENGINE_WARN("You are creating a point light with a non-point light type in your params, are you sure?");
    this->type = static_cast<int>(type);
    this->intensity = intensity;
    this->range = range;
    this->position = glm::vec4(position, 1.0);
    this->color = color;
}
NAMESPACE_END