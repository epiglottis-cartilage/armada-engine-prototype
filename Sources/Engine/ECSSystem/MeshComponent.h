//
// Created by phage on 10/18/25.
//

#pragma once


#include <Common.hh>
#include <Component.h>
#include <Shader.hh>

NAMESPACE_BEGIN

class Model;

class MeshComponent : public Component{

public:
      MeshComponent() = delete;
      MeshComponent(const fs::path modelfile, Shader* shader);
      ~MeshComponent();

      Model* modelptr = nullptr;

      bool visible = true;
      bool shadow = true;

      void tick(float deltatime) override ;
private:
};
NAMESPACE_END
