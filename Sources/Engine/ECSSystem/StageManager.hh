#pragma once

#include <Common.hh>

//unorder map stl, only used here so i am not using "using"
#include <unordered_map>


//this module is coupling Model class for temperal solution
#include <Entity.hh>
#include <Component.h>
#include <TransformComponent.h>
#include <MeshComponent.h>
#include <NameComponent.hh>

NAMESPACE_BEGIN
struct RenderContext;

using StateManager = entt::registry;

class TransformSystem
{
public:
    TransformSystem(StateManager& stateManager)
    {this->enttregistry = &stateManager;}
    void tick(float deltatime)
    {
        //do sth here
    }

private:
    StateManager* enttregistry;
};

class MeshSystem{
public:
    MeshSystem(RenderContext& rendercontext, StateManager& stateManager);


    void tick(float deltatime);
private:
    StateManager* enttregistry;
    RenderContext* rendercontext;
};



NAMESPACE_END