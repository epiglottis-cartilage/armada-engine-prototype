#pragma once

#include <Common.hh>

//unorder map stl, only used here so i am not using "using"
#include <unordered_map>


//this module is coupling Model class for temperal solution
#include <Entity.hh>

NAMESPACE_BEGIN



class StateManager{
public:
    StateManager();
    ~StateManager();

    void addEntity(shared_ptr<Entity> entity);
    void removeEntity(EntityId id);

    const std::unordered_map<EntityId, shared_ptr<Entity>>& getEntities() const {
        return this->entities;
    }

private:
    std::unordered_map<EntityId, shared_ptr<Entity>> entities;
};


NAMESPACE_END