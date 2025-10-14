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


    

    fleet::Shader* phongShader = gameengine->getRenderSystem()->getShaderManager()->getOrCreate("Phong");

    


    //always get dir using asset system
    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fs::path modelfile = modeldir / "fense" / "fense.obj";

    //use path if possible to accesss new features
    fleet::Model* woodfense = new fleet::Model{modelfile};
    //bind shader to model
    woodfense->setShader(phongShader);

    fleet::Model* ironfense = new fleet::Model(modeldir / "fense2" / "fense.obj");
    ironfense->setShader(phongShader);

//    fleet::Model* terrain = new fleet::Model(modeldir / "Rock_Terrain3_SF" / "Rock_Terrain3_SF.obj");
//    terrain->setShader(phongShader);

    fleet::Model* heli = new fleet::Model(modeldir / "mi35m" / "MI-35M.obj");
    heli->setShader(phongShader);

    

    //add model to stage manager to display
    EntityPtr woodfenseptr = std::make_shared<fleet::Entity>(woodfense);
    gameengine->getStateManager()->addEntity(woodfenseptr);
    auto model1transform = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.0f, -5.0f));
    woodfenseptr->setTransform(model1transform);

    EntityPtr ironfenseptr = std::make_shared<fleet::Entity>(ironfense);
    gameengine->getStateManager()->addEntity(ironfenseptr);
    auto model2transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -5.0f));
    ironfenseptr->setTransform(model2transform);

//    EntityPtr terrainptr = std::make_shared<fleet::Entity>(terrain);
//    gameengine->getStateManager()->addEntity(terrainptr);
 

    EntityPtr heliptr = std::make_shared<fleet::Entity>(heli);
    gameengine->getStateManager()->addEntity(heliptr);
    auto helitransform = glm::translate(
        glm::rotate(
            glm::rotate(
                glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f)
            ),
            glm::radians(45.0f), 
            glm::vec3(0.0f, 1.0f, 0.0f)
        )
        , 
        glm::vec3(2.0f, 5.0f, -10.0f)
    );
    heliptr->setTransform(helitransform);
    

    fleet::Camera* camera = gameengine->engineCreateCamera(glm::vec3(0.0f, 0.0f, 3.0f), 70.0f);
    //bind active camera to viewport
    gameengine->setCurrentCamera(camera);
    camera->setCameraSensitivity(glm::vec3(1.0f));

    


    //now enter actual game main loop.
    gameengine->run([](float) {});
    gameengine->shutdown();

    

    return 0;
}