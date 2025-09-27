#include <Engine.hh>
#include <ShaderManager.hh>
#include <glm/glm.hpp>
#include <Main.hh>

#include <memory>

using EntityPtr = std::shared_ptr<fleet::Entity>;

#define suppose_to_have_function_here

int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a2
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};
    gameengine->init();

    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fs::path modelfile = modeldir / "backpack.obj";

    fleet::Shader* generalshader = new fleet::Shader{
        gameengine->getAssetSystem()->getShaderDir() / "universeVertexShader.vert",
        gameengine->getAssetSystem()->getShaderDir() / "fragmentshader.frag"
    };
    gameengine->getRenderSystem()->getShaderManager()->bindUBO(fleet::UBOType::Camera, generalshader);

    fleet::Model* testingmodel = new fleet::Model{modelfile};
    testingmodel->setShader(generalshader);

    EntityPtr testingmodelptr = std::make_shared<fleet::Entity>(testingmodel);
    gameengine->getStateManager()->addEntity(testingmodelptr);

   
    fleet::Camera* camera = gameengine->engineCreateCamera(glm::vec3(0.0f, 0.0f, 3.0f), 90.0f);
    gameengine->setCurrentCamera(camera);

    
    gameengine->run([](float) {});
    gameengine->shutdown();

    return 0;
}