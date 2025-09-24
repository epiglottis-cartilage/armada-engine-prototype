#include <engine.hh>

#define suppose_to_have_function_here

int main(int argc, char** argv){


    //debug build 0x000000xxxxxx000000a1
    fleet::Engine* gameengine = new fleet::Engine{"sandboxtest", "0.0.1"};

    gameengine->init();
    gameengine->run(suppose_to_have_function_here);
    gameengine->shutdown();

    return 0;
}