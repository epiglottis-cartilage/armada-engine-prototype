//
// Created by phage on 10/18/25.
//

#include "TransformComponent.h"
#include <rttr/registration>

NAMESPACE_BEGIN
TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
    this->position[buffer] = pos;
    this->rotation[buffer] = rot;
    this->scale[buffer] = scale;

    this->position[current] = pos;
    this->rotation[current] = rot;
    this->scale[current] = scale;
}

void TransformComponent::tick(float deltatime) {
    std::swap(position[current], position[buffer]);
    std::swap(rotation[current], rotation[buffer]);
    std::swap(   scale[current],    scale[buffer]);
}

glm::mat4 TransformComponent::getTransformMat() {
    glm::mat4 result = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(result, position[current]);
    glm::mat4 rotate = glm::yawPitchRoll(glm::radians(rotation[current].y), glm::radians(rotation[current].x), glm::radians(rotation[current].z));
    glm::mat4 scalemat = glm::scale(result, this->scale[current]);
    return (translate * rotate * scalemat);
}

//rttr registry
RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<TransformComponent>("TransformComponent")
        // 注册构造函数
        .constructor<>()
        .constructor<glm::vec3, glm::vec3, glm::vec3>()

        // 注册字段
        .property("position", &TransformComponent::getPosition, &TransformComponent::setPosition)
        .property("rotation", &TransformComponent::getRotation, &TransformComponent::setRotation)
        .property("scale",    &TransformComponent::getScale,    &TransformComponent::setScale)
        ;
}


NAMESPACE_END