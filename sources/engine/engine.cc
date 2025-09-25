#include <engine.hh>


NAMESPACE_BEGIN

//global null ptr to engine instance itself
Engine* gameEngine;

Engine::Engine(string gamename, string gameversion):
aGamename(gamename),
aGameversion(gameversion)
{

    std::filesystem::path exePath = std::filesystem::current_path() / CONFIG_FILE_NAME;
    this->aConfig = new Config{ exePath.string() };

}


void Engine::init(){
    aAppContext = new AppContext{};
    aAppContext->aIsInited = true;
    aAppContext->aShouldQuit = false;

    aRenderSystem = new RenderSystem{aConfig->cfgrendersystem};
    aAssetSystem = new AssetSystem{aConfig->cfgassetsystem};

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