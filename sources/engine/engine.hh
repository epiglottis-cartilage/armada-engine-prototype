#pragma once

#include <common.hh>
#include <camera.hh>
#include <rendersystem.hh>

//namespace: fleet::xxx

NAMESPACE_BEGIN

struct AppContext {
    bool aIsRunning = false;
    bool aIsInited = false;
    bool aShouldQuit = false;

};

class FLEET_API Engine {

public:
    Engine(string gamename, string gameversion);

    ~Engine() = default;


    void init();

    void run();
    void shutdown();


    AppContext* getAppContext() { return aAppContext; }
    RenderSystem* getRenderSystem() { return aRenderSystem; }
    Camera* getCurrentCamera() { return aCurrentCamera; }

private:
    string aGamename;
    string aGameversion;
    AppContext* aAppContext;
    RenderSystem* aRenderSystem;
    

    Camera* aCurrentCamera;


};

NAMESPACE_END