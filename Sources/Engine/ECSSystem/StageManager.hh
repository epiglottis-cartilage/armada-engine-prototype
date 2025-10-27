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
#include <LightComponent.hh>

NAMESPACE_BEGIN
struct RenderContext;

using StateManager = entt::registry;

class TransformSystem
{
public:
    TransformSystem(StateManager& stateManager) : enttregistry(&stateManager) {};
    void tick(float deltatime);

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

class LightSystem {
    friend LightComponent;
public:
    LightSystem(StateManager& stateManager): enttregistry(&stateManager) {};
    void tick(float deltatime);
private:
    int lightnums = 0;
    bool numsdirty = true;
    void init();
    StateManager* enttregistry;
};


NAMESPACE_END