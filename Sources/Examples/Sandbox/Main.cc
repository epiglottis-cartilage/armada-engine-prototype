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


    fleet::Shader* phongShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("Phong");


    //use path if possible to accesss new features
    fleet::Model* testingmodel = new fleet::Model{modelfile};
    //bind shader to model
    auto generalshader = phongShader;
    testingmodel->setShader(generalshader);

    fleet::Model* testingmodel2 = new fleet::Model(modeldir / "fense2" / "fense.obj");
    testingmodel2->setShader(generalshader);

//    fleet::Model* testingmodel3 = new fleet::Model(modeldir / "Rock_Terrain3_SF" / "Rock_Terrain3_SF.obj");
//    testingmodel3->setShader(generalshader);


    //add model to stage manager to display
    EntityPtr testingmodelptr = std::make_shared<fleet::Entity>(testingmodel);
    gameengine->getStateManager()->addEntity(testingmodelptr);
    auto model1transform = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.0f, -5.0f));
    testingmodelptr->setTransform(model1transform);

    EntityPtr testingmodelptr2 = std::make_shared<fleet::Entity>(testingmodel2);
    gameengine->getStateManager()->addEntity(testingmodelptr2);
    auto model2transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -5.0f));
    testingmodelptr2->setTransform(model2transform);

//    EntityPtr testingmodelptr3 = std::make_shared<fleet::Entity>(testingmodel3);
//    gameengine->getStateManager()->addEntity(testingmodelptr3);
 

    fleet::Camera* camera = gameengine->engineCreateCamera(glm::vec3(0.0f, 0.0f, 3.0f), 70.0f);
    //bind active camera to viewport
    gameengine->setCurrentCamera(camera);
    camera->setCameraSensitivity(glm::vec3(1.0f));

    

    //now enter actual game main loop.
    gameengine->run([](float) {});
    gameengine->shutdown();

    

    return 0;
}