//
// Created by phage on 10/18/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <Common.hh>
#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

NAMESPACE_BEGIN
class TransformComponent :
public Component
{
public:
    TransformComponent() = default;
    TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);


    void tick(float deltatime) override;
    void setPosition(glm::vec3 position){this->position[buffer] = position;isdirty = true;};
    void setRotation(glm::vec3 rotation){this->rotation[buffer] = rotation;isdirty = true;};
    void setScale(glm::vec3 scale){this->scale[buffer] = scale;isdirty = true;};
    glm::vec3 getPosition() {return position[current];};
    glm::vec3 getRotation() {return rotation[current];};
    glm::vec3 getScale() {return scale[current];};

    glm::mat4 getTransformMat() ;
private:
    bool isdirty = false;
    glm::vec3 position[2] = {};
    glm::vec3 rotation[2] = {};
    glm::vec3 scale[2] = {};
    int current = 0;//always read the 0, 1 always be buffer
    int buffer =  1;
};
NAMESPACE_END

#endif //TRANSFORMCOMPONENT_H
