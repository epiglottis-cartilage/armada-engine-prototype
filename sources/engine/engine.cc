#include <engine.hh>

NAMESPACE_BEGIN

//global null ptr to engine instance itself
Engine* gameEngine;

Engine::Engine(string gamename, string gameversion):
aGamename(gamename),
aGameversion(gameversion)
{

}


void Engine::init(){
    aAppContext = new AppContext{};
    aAppContext->aIsInited = true;
    aAppContext->aShouldQuit = false;

    aRenderSystem = new RenderSystem{};


    aAppContext->aIsInited = true;
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
        
        //delta accmulate
    }

}

void Engine::shutdown(){
}

NAMESPACE_END