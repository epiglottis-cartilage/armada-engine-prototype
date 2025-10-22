#include <Engine.hh>
#include <FpsCamera.hh>
#include <ShaderManager.hh>
#include <glm/glm.hpp>
#include <Main.hh>
#include <memory>

using EntityPtr = std::shared_ptr<fleet::Entity>;


int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a3
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};
    gameengine->init();


    fleet::Shader* phongShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("Phong");


    //always get dir using asset system
    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fs::path apc_file = modeldir / "ba_stryker_icv.glb";

    //use path if possible to accesss new features
    fleet::Model* apcModel = new fleet::Model{apc_file};
    //bind shader to model
    apcModel->setShader(phongShader);

    fleet::Model* terrain = new fleet::Model(modeldir / "terraintest.glb");
    terrain->setShader(phongShader);

    fleet::Model* cvchelmet = new fleet::Model(modeldir / "cvchelmet.glb");
    cvchelmet->setShader(phongShader);

    fleet::Model* helimodel = new fleet::Model(modeldir / "mi35.glb");
    helimodel->setShader(phongShader);

    

    //add model to stage manager to display
    fleet::StateManager* gSceneManager = gameengine->getStateManager();
    fleet::Entity apc = gSceneManager->create();
    //add entity with location
    gSceneManager->emplace<fleet::NameComponent>(apc, "Armored APC");
    gSceneManager->emplace<fleet::TransformComponent>(
        apc,
        glm::vec3(1.0f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.0f)
    );
    //add entity with model
    gSceneManager->emplace<fleet::MeshComponent>(
        apc,
        apcModel
    );

    //add a heli model
    fleet::Entity heli = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(heli, "Mi-35");
    gSceneManager->emplace<fleet::TransformComponent>(
        heli,
        glm::vec3(5.0f, 10.0f, -10.0f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.0f)
    );
    //add entity with model
    gSceneManager->emplace<fleet::MeshComponent>(
        heli,
        helimodel
    );

    

    //Example of using subscriber based input manager
    auto* geventmanager = gameengine->getEventManager();
    geventmanager->subscribe(fleet::EventType::KeyPressed, [gSceneManager, apc](const fleet::Event& e){
        auto& keyevent = static_cast<const fleet::KeyPressedEvent&>(e);
        if (keyevent.key == SDLK_r) {
            auto& tmp = gSceneManager->get<fleet::TransformComponent>(apc);
            tmp.setPosition(tmp.getPosition() + glm::vec3{0.0f, 0.0f, 0.5f});
        }
    });

    fleet::Entity terrainEnt = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(terrainEnt, "Testing Ground");
    gSceneManager->emplace<fleet::TransformComponent>(
        terrainEnt,
        glm::vec3(0.0f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(1.0f)
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        terrainEnt,
        terrain
    );



    fleet::FPSCamera* camera = new fleet::FPSCamera{glm::vec3{0.0f, 5.0f, 5.0f}, 70.0f};
    camera->setCameraProjectionMatrix(
        glm::perspective(glm::radians(70.0f), 16.0f/9.0f, 0.1f, 1000.0f)
    );
    //bind active camera to viewport
    gameengine->setCurrentCamera(camera);
    camera->setCameraSensitivity(glm::vec3(1.0f));

    


    //now enter actual game main loop.
    gameengine->run([](float) {});
    gameengine->shutdown();

    

    return 0;
}