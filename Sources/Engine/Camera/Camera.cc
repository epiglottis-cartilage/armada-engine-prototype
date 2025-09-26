#include "Camera.hh"

NAMESPACE_BEGIN

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
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
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
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
}


void Camera::syncCameraAngleData(
    float pitchoffset, float yawoffset, float rolloffset
){

    if(enableDeadZone){
        if(abs(pitchoffset) < deadZoneX)
            pitchoffset = 0.0f;
        if(abs(yawoffset) < deadZoneY)
            yawoffset = 0.0f;
    }
    
    #ifdef DEBUG
    std::cout << "pitch: " << pitchoffset << " yaw: " << yawoffset << " roll: " << rolloffset << std::endl;
    #endif
    pitchNum += pitchoffset * sensitivity.y;
    #ifdef DEBUG
    std::cout << "pitchNum: " << pitchNum << std::endl;
    #endif

    if(pitchNum > PITCHUP_LIMIT) pitchNum = PITCHUP_LIMIT;
    if(pitchNum < PITCHDOWN_LIMIT) pitchNum = PITCHDOWN_LIMIT;
    #ifdef DEBUG
    std::cout << "pitchNum After Convert: " << pitchNum << std::endl;
    #endif
    yawNum += yawoffset * sensitivity.x;
    yawNum = fmod(yawNum, 360.0f);
    rollNum += rolloffset * sensitivity.z;

//    updateCamera();
}

//void Camera::syncCameraPositionData(
//    float deltaTime, glm::vec3 direction
//){
////    position += direction * deltaTime * cameraSpeed;
//    if(direction.x > 0)
//        position += glm::cross(cameraDirection, cameraUp) * deltaTime * cameraSpeed;
//    else if(direction.x < 0)
//        position -= glm::cross(cameraDirection, cameraUp) * deltaTime * cameraSpeed;
//    else if(direction.y > 0)
//        position += cameraUp * deltaTime * cameraSpeed;
//    else if(direction.y < 0)
//        position -= cameraUp * deltaTime * cameraSpeed;
//    else if(direction.z > 0)
//        position -= cameraDirection * deltaTime * cameraSpeed;
//    else if(direction.z < 0)
//        position += cameraDirection * deltaTime * cameraSpeed;
//
////    position += cameraDirection * deltaTime * cameraSpeed;
//    updateCamera();
//}
//
////update the Camera using the value saved in xxxNum. 
////This function is often called after syncCameraPositionData or syncCameraAngleData, 
//glm::mat4 Camera::updateCamera(){
//
//    cameraDirection = glm::vec3(
//        cos(glm::radians(pitchNum)) * sin(glm::radians(yawNum)), 
//        sin(glm::radians(pitchNum)),
//        -cos(glm::radians(pitchNum)) * cos(glm::radians(yawNum))
//    );
//    cameraDirection = glm::normalize(cameraDirection);
//
//    #ifdef DEBUG
//    std::cout << "cameraDirection: " << cameraDirection.x << " " << cameraDirection.y << " " << cameraDirection.z << std::endl;
//    #endif
//
//    cameraUp = glm::vec3(
//        cos(glm::radians(pitchNum + 90)) * sin(glm::radians(yawNum )),
//        sin(glm::radians(pitchNum + 90)),
//        -cos(glm::radians(pitchNum + 90)) * cos(glm::radians(yawNum))
//    );
//    
//    #ifdef DEBUG
//    std::cout << "cameraUp: " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
//    #endif
//
//    glm::mat4 matrixView = glm::lookAt(position, position + cameraDirection, cameraUp);
//    return matrixView;
//}


NAMESPACE_END















