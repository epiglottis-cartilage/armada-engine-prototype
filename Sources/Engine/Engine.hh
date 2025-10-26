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
#include <EventManager.hh>
#include <InputManager.hh>

//namespace: fleet::xxx


NAMESPACE_BEGIN

using namespace std;

using EngineCallbackFunction = std::function <void(float)>;


class FLEET_API Engine {

public:
    /*
    if not explicit giving config path, 
    then executable will look at its working directory for configs file*/
    Engine(string gamename, string gameversion);
    ~Engine() = default;

    void init();
    void run(EngineCallbackFunction gamelogic);
    void shutdown();

    void setCurrentCamera(Camera* camera) { aAppContext->aRenderContext->aCurrentCamera = camera; }
    

    AppContext* getAppContext() { return aAppContext.get(); }
    RenderSystem* getRenderSystem() { return aRenderSystem.get(); }
    UIDrawSystem* getUIDrawSystem() { return aUIDrawSystem.get(); }
    AssetSystem* getAssetSystem() { return aAssetSystem.get(); }
    LoggerPtr getLogger() { return aLogger; }
    StateManager* getStateManager() { return aStateManager.get(); }
    MeshSystem* getMeshSystem() { return aMeshSystem.get(); }
    TransformSystem* getTransformSystem() { return aTransformSystem.get(); }
    LightSystem* getLightSystem() { return aLightSystem.get(); }
    EventManager* getEventManager() { return aEventManager.get(); }
    InputManager* getInputManager() { return aInputManager.get(); }
private:
    string aGamename;
    string aGameversion;
    LoggerPtr aLogger;

    unique_ptr<AppContext> aAppContext;
    unique_ptr<RenderSystem> aRenderSystem;
    unique_ptr<UIDrawSystem> aUIDrawSystem;
    unique_ptr<AssetSystem> aAssetSystem;
    unique_ptr<StateManager> aStateManager;
    unique_ptr<TransformSystem> aTransformSystem;
    unique_ptr<LightSystem> aLightSystem;
    unique_ptr<MeshSystem> aMeshSystem;
    unique_ptr<EventManager>  aEventManager;
    unique_ptr<InputManager> aInputManager;



    Config* aConfig;
};

NAMESPACE_END