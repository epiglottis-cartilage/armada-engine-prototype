#include <Engine.hh>
#include <FpsCamera.hh>
#include <ShaderManager.hh>
#include <glm/glm.hpp>
#include <Main.hh>
#include <memory>

using EntityPtr = std::shared_ptr<fleet::Entity>;


int main(int argc, char** argv){


    auto* gameengine = new fleet::Engine{"Sandbox", "0.0.5"};
    gameengine->init();

    ENGINE_DEBUG("size debug: lightstruct: {} lightbuffer: {}, sizeof int: {}", 
        sizeof(fleet::gpuLightStruct), 
        sizeof(fleet::LightBuffer),
        sizeof(int)
    );


    fleet::Shader* phongShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("Phong");
    fleet::Shader* lightShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("Light");
    fleet::Shader* debugphongShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("DebugPhong");


    //always get dir using asset system
    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fs::path apc_file = modeldir / "ba_stryker_icv.glb";

    //add model to stage manager to display
    fleet::StateManager* gSceneManager = gameengine->getStateManager();
    fleet::Entity apc = gSceneManager->create();
    //add entity with location
    gSceneManager->emplace<fleet::NameComponent>(apc, "Armored APC");
    gSceneManager->emplace<fleet::TransformComponent>(
        apc,
        glm::vec3(1.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
    );
    //add entity with model
    gSceneManager->emplace<fleet::MeshComponent>(
        apc,
        apc_file,
        phongShader
    );

    fleet::Entity smallPointLightEnt = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(smallPointLightEnt, "Small Point Light");
    gSceneManager->emplace<fleet::TransformComponent>(
        smallPointLightEnt,
        glm::vec3(3.0f),
        glm::vec3(0.0f),
        glm::vec3(0.1f)
    );
    gSceneManager->emplace<fleet::LightComponent>(
        smallPointLightEnt,
        lightShader,
        fleet::typeLight::Point,
        glm::vec4{1.0f, 0.435f, 0.0f, 1.0f},
        0.8f,
        30.0f
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        smallPointLightEnt,
        modeldir / "cvchelmet.glb",
        lightShader
    );
    //Warning, this interface will be changed without backward support in next release

    fleet::Entity sunDirectionLight = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(sunDirectionLight, "Sun Directional Light");
    gSceneManager->emplace<fleet::TransformComponent>(
        sunDirectionLight,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        sunDirectionLight,
        modeldir / "minuszarrow.glb",
		lightShader
	);
    gSceneManager->emplace<fleet::LightComponent>(
        sunDirectionLight,
        lightShader,
        fleet::typeLight::Directional,
        glm::vec4{0.0f, 0.414f, 1.0f, 1.0f},
        1.0f,
        100.0f
    );

    //create a house
    fleet::Entity pbrhelmet = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(pbrhelmet, "pbr helmet");
    gSceneManager->emplace<fleet::TransformComponent>(
        pbrhelmet,
        glm::vec3{0.0f},
        glm::vec3(0.0f),
        glm::vec3{1.0f}
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        pbrhelmet,
        modeldir / "damagedhelmet.glb",
        phongShader
    );

    //create a terrain
    fleet::Entity terrainEntOg = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(terrainEntOg, "Testing Ground");
    gSceneManager->emplace<fleet::TransformComponent>(
        terrainEntOg,
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        terrainEntOg,
        modeldir / "terraintest.glb",
        phongShader
    );
    fleet::Entity terrainEnt = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(terrainEnt, "Ground Normal");
    gSceneManager->emplace<fleet::TransformComponent>(
        terrainEnt,
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
    );
    gSceneManager->emplace<fleet::MeshComponent>(
        terrainEnt,
        modeldir / "terraintest.glb",
        debugphongShader
    );


    //add a heli model
    fleet::Entity heli = gSceneManager->create();
    gSceneManager->emplace<fleet::NameComponent>(heli, "Mi-35");
    gSceneManager->emplace<fleet::TransformComponent>(
        heli,
        glm::vec3(5.0f, 10.0f, -10.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
    );
    //add entity with model
    gSceneManager->emplace<fleet::MeshComponent>(
        heli,
        modeldir / "mi35.glb",
        phongShader
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




    auto* camera = new fleet::FPSCamera{glm::vec3{0.0f, 5.0f, 5.0f}, 70.0f};
    camera->setCameraProjectionMatrix(
        glm::perspective(glm::radians(70.0f), 16.0f/9.0f, 0.1f, 1000.0f)
    );
    //bind active camera to viewport
    gameengine->setCurrentCamera(camera);
    camera->setCameraSensitivity(glm::vec3(1.0f));
    geventmanager->subscribe(
        fleet::EventType::KeyPressed,
        [camera](const fleet::Event& e) {
        auto& keyevent = static_cast<const fleet::KeyPressedEvent&>(e);
        if (keyevent.key == SDLK_UP) {
            camera->setCameraSpeed(camera->getCameraSpeed() + 1.0f);
        }
    });
    geventmanager->subscribe(
        fleet::EventType::KeyPressed,
        [camera](const fleet::Event& e) {
        auto& keyevent = static_cast<const fleet::KeyPressedEvent&>(e);
        if (keyevent.key == SDLK_DOWN) {
            camera->setCameraSpeed(camera->getCameraSpeed() - 1.0f);
        }
    });

    


    //now enter actual game main loop.
    gameengine->run([](float) {});
    gameengine->shutdown();

    

    return 0;
}