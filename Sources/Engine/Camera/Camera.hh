#ifndef CAMERA_HH
#define CAMERA_HH
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <Logger.hh>

#define PITCHUP_LIMIT 75.0f
#define PITCHDOWN_LIMIT -75.0f

class Camera{
public:
    Camera(glm::vec3 position);
    ~Camera() = default;
    
    
    //default axis is: camera direction lies on 0,0,-1, 
    //and the angle is between z-negative amd y-positive, x-positive and z-negative
    //define pitch angle positive increase is rolling up, yaw angle positive increase is rolling to right
    //the user is responsible to set the right yawoffset. such as in SDL the yoffset is inverted.
    void syncCameraAngleData(
        float pitchoffset, float yawoffset, float rolloffset
    );

    void syncCameraPositionData(float deltaTime, glm::vec3 direction);

    //update camera according to the parameters, and return the view matrix
    glm::mat4 updateCamera();   

    //x is yaw , y is pitch, z is roll
    void setCameraSensitivity(glm::vec3 sensitivity){
        sensitivity = sensitivity;
    }
    void setCameraSpeed(float newCameraSpeed){
        cameraSpeed = newCameraSpeed;
    }

    glm::vec3 getCameraPosition(){
        return position;
    }

private:
    glm::vec3 position;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;

    float pitchNum, yawNum, rollNum;
    glm::vec3 sensitivity;
    float cameraSpeed;
    bool enableDeadZone;
    float deadZoneX, deadZoneY;
};

#endif