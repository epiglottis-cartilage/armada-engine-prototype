//
// Created by phage on 10/18/25.
//

#include "TransformComponent.h"

NAMESPACE_BEGIN
void TransformComponent::tick(float deltatime) {


}

glm::mat4 TransformComponent::getTransformMat() {

    glm::mat4 result = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(result, position);
    glm::mat4 rotate = glm::yawPitchRoll(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    glm::mat4 scalemat = glm::scale(result, this->scale);
    return (translate * rotate * scalemat);
}
NAMESPACE_END