#pragma once

#include <Common.hh>
#include <Config.hh>
#include <Camera.hh>
#include <RenderSystem.hh>
#include <StageManager.hh>
#include <ShaderManager.hh>
#include <AssetSystem.hh>
#include <Logger.hh>
#include <functional>
#include <glm/glm.hpp>


//namespace: fleet::xxx



NAMESPACE_BEGIN

using namespace std;

using EngineCallbackFunction = std::function <void(float)>;


class AppContext {

public:

    AppContext() :
        aIsRunning(false),
        aIsInited(false),
        aShouldQuit(false)
    {

    }

    ~AppContext() = default;


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

    void setCurrentCamera(Camera* camera) { aCurrentCamera = camera; }
    

    void run(EngineCallbackFunction gamelogic);
    void shutdown();


    AppContext* getAppContext() { return aAppContext; }
    RenderSystem* getRenderSystem() { return aRenderSystem; }
    RenderContext* getRenderContext() { return aRenderContext; }
    AssetSystem* getAssetSystem() { return aAssetSystem; }
    LoggerPtr getLogger() { return aLogger; }
    Camera* getCurrentCamera() { return aCurrentCamera; }
    StateManager* getStateManager() { return aStateManager; }

private:

    string aGamename;
    string aGameversion;
    AppContext* aAppContext;
    RenderContext* aRenderContext;
    RenderSystem* aRenderSystem;
    AssetSystem* aAssetSystem;
    StateManager* aStateManager;
    LoggerPtr aLogger;
    

    Camera* aCurrentCamera;

    
    Config* aConfig;
    void parseConfig(fs::path configpath);

};

NAMESPACE_END