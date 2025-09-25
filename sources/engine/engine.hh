#pragma once

#include <common.hh>
#include <config.hh>
#include <camera.hh>
#include <rendersystem.hh>
#include <assetsystem.hh>

#include <filesystem>

//namespace: fleet::xxx
namespace fs = std::filesystem;

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
    Camera* getCurrentCamera() { return aCurrentCamera; }

private:

    string aGamename;
    string aGameversion;
    AppContext* aAppContext;
    RenderSystem* aRenderSystem;
    AssetSystem* aAssetSystem;
    

    Camera* aCurrentCamera;

    
    Config* aConfig;
    void parseConfig(fs::path configpath);

};

NAMESPACE_END