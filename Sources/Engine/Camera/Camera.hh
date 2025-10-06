#pragma once

#include <Common.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <Logger.hh>
#include <functional>

//delete this once event listener is done

NAMESPACE_BEGIN


#define PITCHUP_LIMIT 75.0f
#define PITCHDOWN_LIMIT -75.0f

/*
this class should be instanced using `Engine::engineCreateCamera()`. it will give you a default FPS camera.
Currently camera instance need init since it rely on some OpenGL things.
using Engine::initCamera(camera_to_init) will init the camera. It need to be called once
the view matrix and projection matrix is updated per frame inside Camera::ProcessInputUpdateCamera(float dt) function.
To set current camera, use Engine::setCurrentCamera(camera). You only need to call this once.
The active camera is always the last one using above method.
*/
class Camera{
public:
    Camera(glm::vec3 position);
    Camera(glm::vec3 position, float angle);
    ~Camera() = default;
    
    
    //default axis is: camera direction lies on 0,0,-1, 
    //and the angle is between z-negative amd y-positive, x-positive and z-negative
    //define pitch angle positive increase is rolling up, yaw angle positive increase is rolling to right
    //the user is responsible to set the right yawoffset. such as in SDL the yoffset is inverted.
//    void syncCameraAngleData(
//        float pitchoffset, float yawoffset, float rolloffset
//    );


    void setCameraPosition(glm::vec3 newPosition){
        this->position = newPosition;
    }

    void setCameraLookat(glm::vec3 target){
        cameraDirection = glm::normalize(target - position);

    }

    void setCameraUp(glm::vec3 newUp){
        cameraUp = newUp;
    }

    void setCameraViewMatrix(glm::mat4 newView){viewMatrix = newView;}
    void setCameraFOV(float newFov);

    /*this is a temperal solution, because Listener based Event system Unfinished leads to Input manager un-implement, 
    I don't have better choice*/
    //TODO: refactor this function after Input Manager is done
    void ProcessInputUpdateCamera(float dt);

    glm::vec3 getCameraPosition(){return position;}
    glm::vec3 getCameraLookat(){return cameraDirection;}
    glm::vec3 getCameraUp(){return cameraUp;}
    glm::mat4 getViewMatrix(){return viewMatrix;}
    glm::mat4 getProjectionMatrix(){return projectionMatrix;}

    //delete this once event listener is done
    std::function<void ()> onExitCalled;

private:
    glm::vec3 position;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float pitchNum, yawNum, rollNum;
    glm::vec3 sensitivity;
    float cameraSpeed;
    bool enableDeadZone;
    float deadZoneX, deadZoneY;
};

NAMESPACE_END