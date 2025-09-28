#include <Engine.hh>


NAMESPACE_BEGIN

//global null ptr to engine instance itself
Engine* gameEngine;

Engine::Engine(string gamename, string gameversion):
    aGamename(gamename),
    aGameversion(gameversion)
{
}

Camera* Engine::engineCreateCamera(glm::vec3 position, float angle){
    Camera* newCamera = new Camera{position, angle};
    return newCamera;
}

/*
engine::init read config file from the working directory, 
set debug config(also output log to working directory by default) and init all sub systems*/
void Engine::init(){
    fs::path exePath = std::filesystem::current_path() / CONFIG_FILE_NAME;

    ENGINE_VALIDLOCATION(exePath);

    this->aConfig = new Config{ exePath.string() };

    ENGINE_INFO("Config Loaded, now printing some fields:\n{}", aConfig->cfgassetsystem.assetpath);

    aAppContext = new AppContext{};
    aAppContext->aIsInited = true;
    aAppContext->aShouldQuit = false;

    ENGINE_INFO("AppContext create success\n");

    Logger::Init(aConfig->cfgappcontext);
    aLogger = Logger::Get();

    ENGINE_INFO("Logger create success\n");

    //init all systems, assign corresponding fields for later access
    aRenderSystem = new RenderSystem{aConfig->cfgrendersystem};
    aRenderContext = new RenderContext{};

    ENGINE_INFO("RenderSystem create success\n");

    aAssetSystem = new AssetSystem{aConfig->cfgassetsystem};

    ENGINE_INFO("AssetSystem create success\n");


    aStateManager = new StateManager{};

    ENGINE_INFO(" StateManager create success\n");

    //TODO: Add ECS and remove below line
    aRenderSystem->updatestatmanager(aStateManager);


    aAppContext->aIsInited = true;

    ENGINE_INFO("Engine init success\n");
//    delete this->aConfig;
}



/*
this method make sure that game logic is running under 60Hz*/
void Engine::run(EngineCallbackFunction gamelogic){
    auto engineContext = getAppContext();
    while(!engineContext->aShouldQuit){
        //game loop

        const float dt = 1.0f / 60.0f;
        Uint64 previoustime = SDL_GetTicks64();
        Uint64 accumulator = 0.0f;
        //update game logic, will try best to run in 60 Hz
        while(accumulator < dt){

            //update game physics, etc
            //update game physics
            //update game logic
            gamelogic(dt);
            accumulator -= dt;
        }


        //calculate delta

        //process Input
        this->aCurrentCamera->ProcessInputUpdateCamera(dt);

        //render frame(game, ui)
        this->aRenderContext->aCurrentCamera = this->aCurrentCamera;
        this->aRenderContext->deltatime = dt;

        this->aRenderSystem->prerender(
            aRenderContext
        );
        this->aRenderSystem->renderframe(
            aRenderContext
        );
        this->aRenderSystem->postrender(
            aRenderContext
        );
        
        //delta accmulate
        Uint64 currenttime = SDL_GetTicks64();
        accumulator += currenttime - previoustime;
        previoustime = currenttime;
    }

    //deal with some resources shutdown here

}

void Engine::shutdown(){
    delete this->aRenderSystem;

}

NAMESPACE_END