#include <Engine.hh>
#include <glm/glm.hpp>
#include <Main.hh>

#define suppose_to_have_function_here

int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a1
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};
    gameengine->init();

    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    fleet::Model* testingmodel = new fleet::Model{modeldir / "backpack.obj"};

    fs::path shaderdir = gameengine->getAssetSystem()->getShaderDir();
    fleet::ShaderFinal* unishader = new fleet::ShaderFinal{shaderdir / "universeVertexShader.vert", shaderdir / "fragmentshader.frag"};

    fleet::Camera* camera = gameengine->engineCreateCamera(glm::vec3(0.0f, 0.0f, 3.0f), 90.0f);
    gameengine->setCurrentCamera(camera);

    
    gameengine->run([](float) {});
    gameengine->shutdown();

    return 0;
}