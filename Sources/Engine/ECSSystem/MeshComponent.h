//
// Created by phage on 10/18/25.
//

#pragma once


#include <Common.hh>
#include <Component.h>

NAMESPACE_BEGIN

class Model;

class MeshComponent : public Component{

public:
      MeshComponent() = default;
      MeshComponent(Model* modelptr) : modelptr(modelptr) {}

      Model* modelptr;

      bool visible = true;
      bool shadow = true;

      void tick(float deltatime) override ;
private:
};
NAMESPACE_END
