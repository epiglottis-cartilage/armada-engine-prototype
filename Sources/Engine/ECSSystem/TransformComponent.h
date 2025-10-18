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
  TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : position(pos), rotation(rot), scale(scale) {}

  glm::vec3 position = glm::vec3{1.0f};
  glm::vec3 rotation = glm::vec3{0.0f};
  glm::vec3 scale = glm::vec3{1.0f};

  void tick(float deltatime) override;

  glm::mat4 getTransformMat() ;
private:

};
NAMESPACE_END

#endif //TRANSFORMCOMPONENT_H
