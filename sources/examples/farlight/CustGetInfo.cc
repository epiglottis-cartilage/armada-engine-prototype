#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <CustShader.hh>
#include <textureSdlGl.hh>


#include "misc.hh"
#include "spCust.hh"



int main(int argc, char* argv[]){

    SDL_Window* window = init_win_and_gl();

    string prefixShaderSources = "../../";

    string vertexShaderFloor = prefixShaderSources +"shaders/vertFloor.vert";
    string vertLightWhite =prefixShaderSources + "shaders/vertLightWhite.vert";
    string vertBuiLight =prefixShaderSources + "shaders/vertexshader.vert";

    string fragmentShaderSource =prefixShaderSources + "shaders/fragmentshader.frag";
    string fragShaderWhiteLight = prefixShaderSources +"shaders/fragLightWhite.frag";
    string fragShaderLightedObject = prefixShaderSources +"shaders/fragBuiLighting.frag";
    string fragSpecBuiLight = prefixShaderSources +"shaders/fragSpecBuiLight.frag";

    spCust spFloor = spCust(vertexShaderFloor, fragmentShaderSource);
    spCust spLightWhite = spCust(vertLightWhite, fragShaderWhiteLight);
    spCust spBuiLight = spCust(vertBuiLight, fragShaderLightedObject);
    spCust spSpecBui = spCust(vertBuiLight, fragSpecBuiLight);
    
//    delete vertexShaderPrecompiledTri;
//    delete fragmentShaderPrecompiledTri;

    #ifdef DEBUG
    errorposition(__FILE__, __LINE__);
    #endif
    cout << "code execute to stage: after shader compile and link and destroy" << endl;


    string sourceWallTexture = "/home/phage/Pictures/Screenshots/Screenshot_20250513_143013.png";
    string rscLightedTexture = "/home/phage/Documents/render/gl/resources/emerald.jpg";
    TextureSdlGl* texLightedTexture = new TextureSdlGl(rscLightedTexture);
    string sourceFloorTexture = "/home/phage/Documents/render/gl/resources/wall.jpg";
    TextureSdlGl* floorTexture = new TextureSdlGl(sourceFloorTexture);

    GLfloat floor_vertices[] = {
        -0.9f, 0.9f, 0.0f,     0.0f, 1.0f,
        0.9f, 0.9f, 0.0f,      1.0f, 1.0f,
        -0.9f, -0.9f, 0.0f,     0.0f, 0.0f,
        0.9f, -0.9f, 0.0f,     1.0f, 0.0f,
    };

    GLuint indices_square[] = {
        0, 1, 2,
        1, 2, 3,
    };

    GLuint vboFloor, vaoFloor, vboFloorIndices;
    glGenVertexArrays(1, &vaoFloor);
    glBindVertexArray(vaoFloor);

        glGenBuffers(1, &vboFloorIndices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboFloorIndices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);

        glGenBuffers(1, &vboFloor);
        glBindBuffer(GL_ARRAY_BUFFER, vboFloor);
        glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertices), floor_vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    glBindVertexArray(0);


//    float example_vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
    GLfloat example_vertices[] = {
        // positions          // normals           // texture coords
        // back face (z = -0.5)
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  // top-right
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  // top-left
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  // bottom-left

        // front face (z = 0.5)
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // top-right
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // top-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // bottom-left

        // left face (x = -0.5)
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // top-right
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // top-left
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // bottom-left
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // bottom-left
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // bottom-right
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // top-right

        // right face (x = 0.5)
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // top-left
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // top-right
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // bottom-right
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // bottom-right
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // bottom-left
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // top-left

        // bottom face (y = -0.5)
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // top-right
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  // top-left
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // bottom-left
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // top-right

        // top face (y = 0.5)
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // top-left
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // top-right
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // bottom-right
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f   // top-left
    };


    cerr << "code execute to stage: coord set, before allocate" << endl;


    GLuint vaoLightedObjectCube, vboSquare;
    glGenVertexArrays(1, &vaoLightedObjectCube);
    glBindVertexArray(vaoLightedObjectCube);

        glGenBuffers(1, &vboSquare);
        glBindBuffer(GL_ARRAY_BUFFER, vboSquare);
        glBufferData(GL_ARRAY_BUFFER, sizeof(example_vertices), example_vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

    glBindVertexArray(0);









    GLuint vaoLightCube;
    glGenVertexArrays(1, &vaoLightCube);
    glBindVertexArray(vaoLightCube);

        glBindBuffer(GL_ARRAY_BUFFER, vboSquare);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    GLuint vaoArrays[] = {vaoFloor, vaoLightCube, vaoLightedObjectCube};
    GLuint textureArrays[] = {floorTexture->getTextureId(), texLightedTexture->getTextureId()};
    //00 is for floor, 01 is whitelight, 02 is for lighted object
    GLuint shaderPrograms[] = {spFloor.getGSP(), spLightWhite.getGSP(), spSpecBui.getGSP(), spBuiLight.getGSP()};


    cout << "code execute to stage: before render" << endl;

    errorposition(__FILE__, __LINE__);


    render(window, shaderPrograms, vaoArrays, textureArrays);

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





