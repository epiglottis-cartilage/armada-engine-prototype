#pragma once
#include <Common.hh>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <Logger.hh>

//decoupling possible? 
#include <assimp/Texture.h>

using namespace std;

NAMESPACE_BEGIN
class TextureSdlGl {

public:
    TextureSdlGl(string filepathTexture);
    GLuint getTextureId() {
        return textureId;
    }
    TextureSdlGl(const aiTexture* inmemptr);


    ~TextureSdlGl() {
    }

private:
    GLuint textureId;
    GLenum errorClass;
};



NAMESPACE_END