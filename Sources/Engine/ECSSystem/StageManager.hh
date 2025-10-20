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

using StateManagerPtr = unique_ptr<entt::registry>;

class TransformSystem
{
public:
    TransformSystem(StateManagerPtr& stateManager) :
        enttregistry(stateManager)
    {}
    void tick(float deltatime)
    {
        //do sth here
    }

private:
    StateManagerPtr& enttregistry;
};

class MeshSystem{
public:
    MeshSystem(RenderContext& rendercontext, StateManagerPtr& stateManager) :
        enttregistry(stateManager),
        rendercontext(rendercontext){};
    void tick(float deltatime);
private:
    StateManagerPtr& enttregistry;
    RenderContext& rendercontext;
};



NAMESPACE_END