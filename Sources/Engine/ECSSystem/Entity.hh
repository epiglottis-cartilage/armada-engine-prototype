#pragma once

#include <Common.hh>
#include <Model.hh>

#include <glm/glm.hpp>

NAMESPACE_BEGIN

using EntityId = Uint64;


class Entity{

public:
    Entity(){
        id = nextId++;
    };
    ~Entity();

    Entity(Model* m) : model(m) {
        id = nextId++;
    }

    void setModel(Model* m){
        this->model = m;
    }
    Model* getModel() const{
        return this->model;
    }

    void setTransform(const glm::mat4& mat){
        this->transform = mat;
    }
    glm::mat4 getTransform() const{
        return this->transform;
    }
    void setShown(bool show){
        this->visible = show;
    }
    bool getVisibility() const{
        return this->visible;
    }
    EntityId getId() const{
        return this->id;
    }


private:
    //TODO: stop using such thread-unsafe id generator
    static EntityId nextId;

    bool visible = true;
    EntityId id;

    Model* model;

    //todo: move the model matrix from Model class to here!
    glm::mat4 transform;
    

};
NAMESPACE_END