#include "Camera.hh"

#include <imgui_impl_sdl2.h>
#include <GlobalContext.hh>


NAMESPACE_BEGIN

extern AppContext* objptrAppContext;

    Camera::Camera(glm::vec3 position) :
    position(position), 
    cameraDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),

    viewMatrix(glm::lookAt(position, position + cameraDirection, cameraUp)),
    projectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f)),

    pitchNum(0.0f), 
    yawNum(0.0f), 
    rollNum(0.0f), 
    sensitivity(glm::vec3(0.1f, 0.1f, 0.1f)), 
    cameraSpeed(5.0f), 
    enableDeadZone(true), 
    deadZoneX(2.0f), 
    deadZoneY(2.0f)
//    engineAppContext(nullptr)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetRelativeMouseState(NULL, NULL); // 清空残留数据

}

Camera::Camera(glm::vec3 position, float angle) :
    position(position), 
    cameraDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),

    //this params need to update in pre-rendering!
    viewMatrix(glm::lookAt(position, position + cameraDirection, cameraUp)),
    //note: ths second params need to get again since it stores in appcontext!
    projectionMatrix(glm::perspective(glm::radians(angle), 16.0f / 9.0f, 0.1f, 100.0f)),

    pitchNum(0.0f), 
    yawNum(0.0f), 
    rollNum(0.0f), 
    sensitivity(glm::vec3(0.1f, 0.1f, 0.1f)), 
    cameraSpeed(5.0f), 
    enableDeadZone(true), 
    deadZoneX(2.0f), 
    deadZoneY(2.0f)
//    engineAppContext(nullptr)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetRelativeMouseState(NULL, NULL); // 清空残留数据

}


void Camera::UpdateCamera(float dt){
}

NAMESPACE_END