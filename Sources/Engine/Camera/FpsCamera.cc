//
// Created by phage on 10/22/25.
//

#include "FpsCamera.hh"
#include <Engine.hh>

NAMESPACE_BEGIN
extern Engine* objptrGameEngine;

void FPSCamera::UpdateCamera(float dt)
{

    float hoffset = inputmgr->getMouseDeltaX();
    float voffset = -inputmgr->getMouseDeltaY();
    // Update camera angles using mouse offsets
    if (hoffset != 0.0f || voffset != 0.0f) {
        // Apply sensitivity and deadzone
        float pitchOffset = voffset * sensitivity.y;
        float yawOffset = hoffset * sensitivity.x;

        if (enableDeadZone) {
            if (fabs(pitchOffset) < deadZoneY) pitchOffset = 0.0f;
            if (fabs(yawOffset) < deadZoneX) yawOffset = 0.0f;
        }

        pitchNum += pitchOffset;
        pitchNum = glm::clamp(pitchNum, PITCHDOWN_LIMIT, PITCHUP_LIMIT);
        yawNum += yawOffset;
        yawNum = fmod(yawNum, 360.0f);
    }

    // 键盘持续输入
    glm::vec3 forward = glm::normalize(cameraDirection);
    glm::vec3 right = glm::normalize(glm::cross(forward, cameraUp));
    glm::vec3 up = cameraUp;

    glm::vec3 moveDirection(0.0f);
    if (inputmgr->isKeyHeld(SDL_SCANCODE_W)) moveDirection += forward;
    if (inputmgr->isKeyHeld(SDL_SCANCODE_S)) moveDirection -= forward;
    if (inputmgr->isKeyHeld(SDL_SCANCODE_A)) moveDirection -= right;
    if (inputmgr->isKeyHeld(SDL_SCANCODE_D)) moveDirection += right;
    if (inputmgr->isKeyHeld(SDL_SCANCODE_SPACE)) moveDirection += up;
    if (inputmgr->isKeyHeld(SDL_SCANCODE_LCTRL)) moveDirection -= up;

    if (glm::length(moveDirection) > 0.0f)
        position += glm::normalize(moveDirection) * cameraSpeed * dt;

    // Calculate new direction from pitch and yaw
    glm::vec3 front;
    front.x = cos(glm::radians(yawNum)) * cos(glm::radians(pitchNum));
    front.y = sin(glm::radians(pitchNum));
    front.z = sin(glm::radians(yawNum)) * cos(glm::radians(pitchNum));
    cameraDirection = glm::normalize(front);

    // Update view matrix
    viewMatrix = glm::lookAt(position, position + cameraDirection, cameraUp);
    // Optionally update projection matrix if FOV changes
    // projectionMatrix = ...
    return;
}

FPSCamera::FPSCamera(glm::vec3 position, float angle) :
Camera(position, angle)
{
    this->inputmgr = objptrGameEngine->getInputManager();
}


NAMESPACE_END
