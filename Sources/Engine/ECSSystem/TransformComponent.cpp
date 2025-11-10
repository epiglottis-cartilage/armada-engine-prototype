//
// Created by phage on 10/18/25.
//

#include "TransformComponent.h"

#include <glm/gtx/string_cast.hpp>
#include <rttr/registration>
#include "Logger.hh"

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
    ENGINE_DEBUG("before tick: euleraxis angle: {}", glm::to_string(rotation[current]));
    current = buffer;
    buffer = 1 - current;
    position[buffer] = position[current];
    rotation[buffer] = rotation[current];
    scale[buffer] = scale[current];
    ENGINE_DEBUG("after tick: euleraxis angle: {}", glm::to_string(rotation[current]));
}

glm::mat4 TransformComponent::getTransformMat() {
    glm::mat4 result = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(result, position[current]);
    glm::mat4 rotate =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].z), glm::vec3(0,0,1))*
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].x), glm::vec3(1,0,0))*
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].y), glm::vec3(0,1,0));
    glm::mat4 scalemat = glm::scale(result, this->scale[current]);
    return (translate * rotate * scalemat);
}

glm::vec3 TransformComponent::getDirection() {
    glm::mat4 rotate =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].z), glm::vec3(0,0,1))*
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].x), glm::vec3(1,0,0))*
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation[current].y), glm::vec3(0,1,0));
    glm::vec4 front = rotate * glm::vec4{0.0f, 0.0f, -1.0f, 0.0f};
    return glm::normalize(glm::vec3{front});
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