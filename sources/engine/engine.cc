#include <Engine.hh>


NAMESPACE_BEGIN

//global null ptr to engine instance itself
Engine* gameEngine;

Engine::Engine(string gamename, string gameversion):
    aGamename(gamename),
    aGameversion(gameversion)
{
}


/*
engine::init read config file from the working directory, 
set debug config(also output log to working directory by default) and init all sub systems*/
void Engine::init(){
    std::filesystem::path exePath = std::filesystem::current_path() / CONFIG_FILE_NAME;
    this->aConfig = new Config{ exePath.string() };

    aAppContext = new AppContext{};
    aAppContext->aIsInited = true;
    aAppContext->aShouldQuit = false;

    //init all systems, assign corresponding fields for later access
    aRenderSystem = new RenderSystem{aConfig->cfgrendersystem};
    aAssetSystem = new AssetSystem{aConfig->cfgassetsystem};
    Logger::Init(aConfig->cfgappcontext);
    aLogger = Logger::Get();

    aAppContext->aIsInited = true;
//    delete this->aConfig;
}



void Engine::run(){
    auto engineContext = getAppContext();
    while(!engineContext->aShouldQuit){
        //game loop

        //calculate delta

        //process Input
        //update game physics
        //update game logic
        //render frame(game, ui)
        this->aRenderSystem->renderframe();
        
        //delta accmulate
    }

}

void Engine::shutdown(){
}

NAMESPACE_END