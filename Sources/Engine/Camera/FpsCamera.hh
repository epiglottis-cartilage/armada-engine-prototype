//
// Created by phage on 10/22/25.
//

#ifndef FPSCAMERA_HH
#define FPSCAMERA_HH


#include <Common.hh>
#include <Camera.hh>

NAMESPACE_BEGIN

class InputManager;

class FPSCamera : public Camera{

public:
    void UpdateCamera(float dt) override;

    FPSCamera(glm::vec3 position, float angle);
private:
    InputManager* inputmgr;
};

NAMESPACE_END

#endif //FPSCAMERA_HH
