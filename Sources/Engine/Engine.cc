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
    newCamera->onExitCalled = [this]() {
        this->aAppContext->aShouldQuit = true;
    };
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
    ENGINE_INFO("parse some config: {}", aConfig->cfgassetsystem.assetpath);
}



/*
this method make sure that game logic is running under 60Hz*/
void Engine::run(EngineCallbackFunction gamelogic){
    auto engineContext = getAppContext();
    ENGINE_INFO("Engine run start\n");
    ENGINE_INFO("app context content: {} {}", engineContext->aShouldQuit, engineContext->aIsInited);
    ENGINE_INFO("Engine run start\n");
    while(!engineContext->aShouldQuit){
        //game loop
//        ENGINE_INFO("one Engine loop start\n");


        const float dt = 1.0f / 60.0f;
        Uint64 previoustime = SDL_GetTicks64();
        Uint64 accumulator = 0.0f;
        //update game logic, will try best to run in 60 Hz
        while(accumulator >= dt){

            //update game physics, etc
            //update game physics
            //update game logic
            gamelogic(dt);
            accumulator -= dt;
        }



//        ENGINE_INFO("updating camera");
        //process Input, update camera current status, like view matrix, ...
        if(this->aRenderContext->aCurrentCamera != nullptr){
            aRenderContext->aCurrentCamera->ProcessInputUpdateCamera(dt);
        }
        //delta time field is not used currently
        this->aRenderContext->deltatime = dt;


//        ENGINE_INFO("rendering");
        //transmit camera data, render frame, etc
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
//        ENGINE_INFO("one Engine loop end\n");
    }

}

void Engine::shutdown(){
    delete this->aConfig;
    delete this->aAppContext;
    delete this->aAssetSystem;
    delete this->aStateManager;
    delete this->aRenderContext;
    delete this->aRenderSystem;
    ENGINE_INFO("Engine shutdown success\n");
    Logger::Shutdown();
}

NAMESPACE_END