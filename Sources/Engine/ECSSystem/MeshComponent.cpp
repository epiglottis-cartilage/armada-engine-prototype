//
// Created by phage on 10/18/25.
//

#include "MeshComponent.h"
#include <Model.hh>

NAMESPACE_BEGIN
void MeshComponent::tick(float deltatime) {
  if (visible) {
    }
}

MeshComponent::MeshComponent(const fs::path modelfile, Shader* shader) :
    modelptr(new Model{modelfile})
{this->modelptr->setShader(shader);};

MeshComponent::~MeshComponent() {
    delete modelptr;
}


NAMESPACE_END