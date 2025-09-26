#ifndef TEXTURESDLGL_HH
#define TEXTURESDLGL_HH
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;

class TextureSdlGl {

public:
    TextureSdlGl(string filepathTexture);
    GLuint getTextureId() {
        return textureId;
    }

    ~TextureSdlGl() {
    }

private:
    GLuint textureId;
    GLenum errorClass;
};



#endif // TEXTURESDLGL_HH