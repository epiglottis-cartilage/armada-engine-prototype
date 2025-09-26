#include <cmath>
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <ShaderFinal.hh>
#include <textureSdlGl.hh>


#include "misc.hh"

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = init_win_and_gl();


    //compiling shaders...... this will takes two years
    //        /\ /\ /\
    //        || || ||
    //    that just a joke.......

    fs::path pathAllResourcesRoot = { string{ argv[1] } };

    fs::path vshaderLocation = pathAllResourcesRoot / "shaders" / "vertexshader.vert";
	fs::path fshaderLocation = pathAllResourcesRoot / "shaders" /"fragmentshader.frag";

    ShaderFinal testingShader = { vshaderLocation.string(), fshaderLocation.string()};


    //now loading models......


    #ifdef DEBUG
    errorposition(__FILE__, __LINE__);
    #endif
    cout << "code execute to stage: after shader compile and link and destroy" << endl;

    cout << "now loading models" << endl;

    fs::path modelpath = pathAllResourcesRoot / "resources" / "model" / "backpack" / "backpack.obj";
    Model testingModel = { modelpath.string()};

    cout << "code execute to stage: before render" << endl;

    errorposition(__FILE__, __LINE__);


    render(window, {testingShader}, {testingModel});

    #ifdef DEBUG
    GLenum errorClass;
    cout << "code execute to stage: after render, before end" << endl;
    while((errorClass = glGetError()) != GL_NO_ERROR){
        cerr << "error class: " << errorClass << endl;
    }
    #endif



//    delete wallTexture;
    return programExit(window);
}





