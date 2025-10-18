#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <Common.hh>
#include <Config.hh>
#include <Camera.hh>
#include <RenderSystem.hh>
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

class AppContext {
public:
    AppContext() :
        aIsRunning(false),
        aIsInited(false),
        aShouldQuit(false)
    {
        aRenderContext = make_unique<RenderContext>();
    }

    unique_ptr<RenderContext> aRenderContext;
    bool aIsRunning ;
    bool aIsInited ;
    bool aShouldQuit;
private:


};

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
    AssetSystem* getAssetSystem() { return aAssetSystem; }
    LoggerPtr getLogger() { return aLogger; }
    StateManagerPtr& getStateManager() { return aStateManager; }
    ecsMeshSystem getMeshSystem() { return aMeshSystem; }
private:
    //TODO: make them all become unique ptr
    string aGamename;
    string aGameversion;
    unique_ptr<AppContext> aAppContext;
    RenderSystem* aRenderSystem;
    AssetSystem* aAssetSystem;
    StateManagerPtr aStateManager;
    unique_ptr<MeshSystem> aMeshSystem;
    LoggerPtr aLogger;
    

    Camera* aCurrentCamera;


    Config* aConfig;
};

NAMESPACE_END