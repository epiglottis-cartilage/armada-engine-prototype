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
//    SDL_Event e;
//    float hoffset = 0.0f, voffset = 0.0f;
//
//    // Process SDL events for camera speed and mouse movement
//    while(SDL_PollEvent(&e)){
//        ImGui_ImplSDL2_ProcessEvent(&e);
//        if (e.type == SDL_QUIT)
//        {
//            this->onExitCalled();
//            break;
//        }
//        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F10) {
//            objptrAppContext->aEditorMode = !objptrAppContext->aEditorMode;
//            objptrAppContext->switchEditorMode();
//        }
//        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F9) {
//            objptrAppContext->aShowEditor = !objptrAppContext->aShowEditor;
//        }
//        if (!objptrAppContext->aEditorMode)
//        {
//            switch (e.type) {
//                //in sdl, x is from left to right, y is from top to bottom
//            case SDL_MOUSEMOTION:
//                hoffset = e.motion.xrel;
//                voffset = -e.motion.yrel;
//                break;
//
//            case SDL_KEYDOWN:
//                switch (e.key.keysym.sym) {
//            case SDLK_UP:
//                cameraSpeed += 0.1f;
//                    break;
//            case SDLK_DOWN:
//                cameraSpeed -= 0.1f;
//                    break;
//
//            default:
//                break;
//                }
//                break;
//
//            default:
//                break;
//            }
//        }
//    }
//
//    // Keyboard state for camera movement
//    const Uint8* keystates = SDL_GetKeyboardState(NULL);
//    glm::vec3 forward = glm::normalize(cameraDirection);
//    glm::vec3 right = glm::normalize(glm::cross(forward, cameraUp));
//    glm::vec3 up = cameraUp;
//
//    glm::vec3 moveDirection(0.0f);
//    if(keystates[SDL_SCANCODE_W]) moveDirection += forward;
//    if(keystates[SDL_SCANCODE_S]) moveDirection -= forward;
//    if(keystates[SDL_SCANCODE_A]) moveDirection -= right;
//    if(keystates[SDL_SCANCODE_D]) moveDirection += right;
//    if(keystates[SDL_SCANCODE_SPACE]) moveDirection += up;
//    if(keystates[SDL_SCANCODE_LCTRL]) moveDirection -= up;
//
//    if (glm::length(moveDirection) > 0.0f)
//        position += glm::normalize(moveDirection) * cameraSpeed * dt;
//
//    // Update camera angles using mouse offsets
//    if (hoffset != 0.0f || voffset != 0.0f) {
//        // Apply sensitivity and deadzone
//        float pitchOffset = voffset * sensitivity.y;
//        float yawOffset = hoffset * sensitivity.x;
//
//        if (enableDeadZone) {
//            if (fabs(pitchOffset) < deadZoneY) pitchOffset = 0.0f;
//            if (fabs(yawOffset) < deadZoneX) yawOffset = 0.0f;
//        }
//
//        pitchNum += pitchOffset;
//        pitchNum = glm::clamp(pitchNum, PITCHDOWN_LIMIT, PITCHUP_LIMIT);
//        yawNum += yawOffset;
//        yawNum = fmod(yawNum, 360.0f);
//    }
//
//    // Calculate new direction from pitch and yaw
//    glm::vec3 front;
//    front.x = cos(glm::radians(yawNum)) * cos(glm::radians(pitchNum));
//    front.y = sin(glm::radians(pitchNum));
//    front.z = sin(glm::radians(yawNum)) * cos(glm::radians(pitchNum));
//    cameraDirection = glm::normalize(front);
//
//    // Update view matrix
//    viewMatrix = glm::lookAt(position, position + cameraDirection, cameraUp);
//    // Optionally update projection matrix if FOV changes
//    // projectionMatrix = ...
//    return;
}








//void Camera::syncCameraAngleData(
//    float pitchoffset, float yawoffset, float rolloffset
//){
//
//    if(enableDeadZone){
//        if(abs(pitchoffset) < deadZoneX)
//            pitchoffset = 0.0f;
//        if(abs(yawoffset) < deadZoneY)
//            yawoffset = 0.0f;
//    }
//    ENGINE_DEBUG("pitch: %.4f yaw: %.4f roll: %.4f\n", pitchoffset, yawoffset, rolloffset);
//    pitchNum += pitchoffset * sensitivity.y;
//    ENGINE_DEBUG("pitchNum: %.4f\n", pitchNum);
//
//    if(pitchNum > PITCHUP_LIMIT) pitchNum = PITCHUP_LIMIT;
//    if(pitchNum < PITCHDOWN_LIMIT) pitchNum = PITCHDOWN_LIMIT;
//    ENGINE_DEBUG("pitchNum After Convert: %.4f\n", pitchNum);
//    yawNum += yawoffset * sensitivity.x;
//    yawNum = fmod(yawNum, 360.0f);
//    rollNum += rolloffset * sensitivity.z;
//
//
//    updateCamera();

//}


NAMESPACE_END