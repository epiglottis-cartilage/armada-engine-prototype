#pragma once

#include <GlobalContext.hh>
#include <Common.hh>
#include <Config.hh>
#include <Camera.hh>
#include <RenderSystem.hh>
#include <UIDrawSystem.hh>
#include <StageManager.hh>
#include <AssetSystem.hh>
#include <Logger.hh>
#include <functional>
#include <glm/glm.hpp>

//namespace: fleet::xxx



NAMESPACE_BEGIN

using namespace std;

using EngineCallbackFunction = std::function <void(float)>;
using ecsMeshSystem = unique_ptr<MeshSystem>&;


class FLEET_API Engine {

public:
    /*
    if not explicit giving config path, 
    then executable will look at its working directory for configs file*/
    Engine(string gamename, string gameversion);

    ~Engine() = default;


    void init();

    Camera* engineCreateCamera(glm::vec3 position, float angle);

    void setCurrentCamera(Camera* camera) { aAppContext->aRenderContext->aCurrentCamera = camera; }
    

    void run(EngineCallbackFunction gamelogic);
    void shutdown();


    AppContext& getAppContext() { return *aAppContext; }
    RenderSystem* getRenderSystem() { return aRenderSystem; }
    UIDrawSystem* getUIDrawSystem() { return aUIDrawSystem.get(); }
    AssetSystem* getAssetSystem() { return aAssetSystem; }
    LoggerPtr getLogger() { return aLogger; }
    StateManagerPtr& getStateManager() { return aStateManager; }
    ecsMeshSystem getMeshSystem() { return aMeshSystem; }
private:
    //TODO: make them all become unique ptr
    string aGamename;
    string aGameversion;
    AppContext* aAppContext;
    RenderSystem* aRenderSystem;
    unique_ptr<UIDrawSystem> aUIDrawSystem;
    AssetSystem* aAssetSystem;
    StateManagerPtr aStateManager;
    unique_ptr<MeshSystem> aMeshSystem;
    LoggerPtr aLogger;
    

    Camera* aCurrentCamera;


    Config* aConfig;
};

NAMESPACE_END