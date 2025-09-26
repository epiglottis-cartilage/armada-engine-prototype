#include <Engine.hh>
#include <Main.hh>

#define suppose_to_have_function_here

int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a1
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};
    gameengine->init();

    fs::path modeldir = gameengine->getAssetSystem()->getModelDir();
    Model* testingmodel = new Model{modeldir / "backpack.obj"};

    fs::path shaderdir = gameengine->getAssetSystem()->getShaderDir();
    ShaderFinal* unishader = new ShaderFinal{shaderdir / "universeVertexShader.vert", shaderdir / "fragmentshader.frag"};

    auto renderer = gameengine->getRenderSystem();
    renderer->submit(testingmodel, unishader);

    
    gameengine->run();
    gameengine->shutdown();

    return 0;
}