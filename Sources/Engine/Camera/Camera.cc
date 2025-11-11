#include "Camera.hh"

#include <imgui_impl_sdl2.h>
#include <GlobalContext.hh>
#include <rttr/registration>

NAMESPACE_BEGIN

extern AppContext* objptrAppContext;

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Camera>("Camera")
        // 注册构造函数
        .constructor<>()

        // 注册字段
        .property("FOV", &Camera::getCameraFOV, &Camera::setCameraFOV)
        .property("Camera Speed", &Camera::cameraSpeed)
        .property("near", &Camera::getCameraNear, &Camera::setCameraNear)
        .property("far", &Camera::getCameraFar, &Camera::setCameraFar)
        ;
}

Camera::Camera(glm::vec3 position, float angle) :
    position(position), 
    cameraDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),


    pitchNum(0.0f), 
    yawNum(0.0f), 
    rollNum(0.0f),
    degreeFOV(angle),
    near(1.0f),far(1500.0f),
    sensitivity(glm::vec3(0.1f, 0.1f, 0.1f)), 
    cameraSpeed(15.0f), 
    enableDeadZone(true), 
    deadZoneX(2.0f), 
    deadZoneY(2.0f),
//    engineAppContext(nullptr)
    //this params need to update in pre-rendering!
    viewMatrix(glm::lookAt(position, position + cameraDirection, cameraUp)),
    //note: ths second params need to get again since it stores in appcontext!
    projectionMatrix(glm::perspective(glm::radians(angle), 16.0f / 9.0f, near, far))
{
    ENGINE_DEBUG("camera ratio:{} near:{} far:{} fov:{}", 16.0f/9.0f, near, far, degreeFOV);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetRelativeMouseState(NULL, NULL); // 清空残留数据

}


void Camera::UpdateCamera(float dt){
}



NAMESPACE_END