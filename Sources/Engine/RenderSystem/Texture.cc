#include "Texture.hh"

TextureSdlGl::TextureSdlGl(string filepathTexture) {
        SDL_Surface *surface = IMG_Load(filepathTexture.c_str());
        if(surface == NULL){
            ENGINE_ERROR("Creating SDL_Surface from filepath Error: %s\n", IMG_GetError());
        }

        //safely force convert into rgba32 format under sdl_surface
        surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        if (surface == NULL){
            ENGINE_ERROR("Safely convert raw SDL_Surface into rgba32 SDL_Surface Error: %s\n", SDL_GetError());
        }
            

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


        ENGINE_DEBUG("Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
                     "After load an image as SDL_Surface and before convert it to GL texture\n");

        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            surface->w,
            surface->h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            surface->pixels
        );
        ENGINE_DEBUG("Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
        "After convert SDL surface to GL texture"
        "if you see this, it means SDL_Surface has been successfully converted to GL texture\n");

        GLenum errorClass;
        while((errorClass = glGetError()) != GL_NO_ERROR){
            ENGINE_ERROR("SDL surface to GL texture Error: %u\n", errorClass);
        }

        glGenerateMipmap(GL_TEXTURE_2D);


        while((errorClass = glGetError()) != GL_NO_ERROR){
            ENGINE_ERROR("GL generate Mipmap Error: %u\n", errorClass);
        }

        ENGINE_DEBUG("Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
                     "after generate Mipmap, before Freeing SDL surface\n"
                    );

        SDL_FreeSurface(surface);
        glBindTexture(GL_TEXTURE_2D, 0);
    }








