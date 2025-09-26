#pragma once

#include <Common.hh>
#include <Config.hh>
#include <Camera.hh>
#include <RenderSystem.hh>
#include <AssetSystem.hh>
#include <Logger.hh>


//namespace: fleet::xxx

NAMESPACE_BEGIN

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

    

    void run();
    void shutdown();


    AppContext* getAppContext() { return aAppContext; }
    RenderSystem* getRenderSystem() { return aRenderSystem; }
    AssetSystem* getAssetSystem() { return aAssetSystem; }
    LoggerPtr getLogger() { return aLogger; }
    Camera* getCurrentCamera() { return aCurrentCamera; }

private:

    string aGamename;
    string aGameversion;
    AppContext* aAppContext;
    RenderSystem* aRenderSystem;
    AssetSystem* aAssetSystem;
    LoggerPtr aLogger;
    

    Camera* aCurrentCamera;

    
    Config* aConfig;
    void parseConfig(fs::path configpath);

};

NAMESPACE_END