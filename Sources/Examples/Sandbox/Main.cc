#include <Engine.hh>
#include <ShaderManager.hh>
#include <glm/glm.hpp>
#include <Main.hh>
#include <memory>

using EntityPtr = std::shared_ptr<fleet::Entity>;


int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a3
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};
    gameengine->init();


    //always get dir using asset system
    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fs::path modelfile = modeldir / "fense" / "fense.obj";


    fs::path shaderdir = gameengine->getAssetSystem()->getShaderDir();
    fleet::Shader* generalshader = new fleet::Shader{
        shaderdir / "universeVertexShader.vert",
        shaderdir / "fragmentshader.frag"
    };
    //Shader instance create api will be re-write in next big release, this is a temporary usage.
    gameengine->getRenderSystem()->getShaderManager()->bindUBO(generalshader);



    //use path if possible to accesss new features
    fleet::Model* testingmodel = new fleet::Model{modelfile};
    //bind shader to model
    testingmodel->setShader(generalshader);


    //add model to stage manager to display
    EntityPtr testingmodelptr = std::make_shared<fleet::Entity>(testingmodel);
    gameengine->getStateManager()->addEntity(testingmodelptr);

 

    fleet::Camera* camera = gameengine->engineCreateCamera(glm::vec3(0.0f, 0.0f, 3.0f), 70.0f);
    //bind active camera to viewport
    gameengine->setCurrentCamera(camera);
    camera->setCameraSensitivity(glm::vec3(1.0f));

    

    //now enter actual game main loop.
    gameengine->run([](float) {});
    gameengine->shutdown();

    

    return 0;
}