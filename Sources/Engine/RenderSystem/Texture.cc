#include "Texture.hh"

NAMESPACE_BEGIN

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


    TextureSdlGl::TextureSdlGl(const aiTexture* inmemptr) {
        SDL_RWops* rw = nullptr;
        SDL_Surface* surface = nullptr;
        if (inmemptr == nullptr) {
            ENGINE_ERROR("Creating TextureSdlGl from aiTexture* Error: input pointer is null\n");
            return;
        }
        if (inmemptr->mHeight == 0) {
            ENGINE_INFO("Creating TextureSDLGL from compressed file format");

            rw = SDL_RWFromConstMem(inmemptr->pcData, inmemptr->mWidth);
            surface = IMG_Load_RW(rw, 1);
        } else {
            ENGINE_INFO("Creating TextureSDLGL from uncompressed file format");
            surface = SDL_CreateRGBSurfaceFrom(
                (void*)inmemptr->pcData,
                inmemptr->mWidth,
                inmemptr->mHeight,
                32,
                inmemptr->mWidth * 4,
                0x000000FF,
                0x0000FF00,
                0x00FF0000,
                0xFF000000
            );

        }
//what is this?????
//        //load from compressed format
//        if (inmemptr->mFormatHint != "rgba8888" && inmemptr->mFormatHint != "argb8888") {
//            ENGINE_ERROR("Creating TextureSdlGl from aiTexture* Error: only support rgba8888 and argb8888 format, got {}\n", inmemptr->mFormatHint);
//            return;
//        }
//
//        SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(
//            (void*)inmemptr->pcData,
//            inmemptr->mWidth,
//            inmemptr->mHeight,
//            32,
//            inmemptr->mWidth * 4,
//            SDL_PIXELFORMAT_RGBA32
//        );
        if(surface == NULL){
            ENGINE_ERROR("Creating SDL_Surface from aiTexture* Error: {}\n", SDL_GetError());
            return;
        }

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        ENGINE_DEBUG("Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(const aiTexture* inmemptr)"
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
            ENGINE_ERROR("GL generate Mipmap Error: {}\n", errorClass);
        }

        ENGINE_DEBUG("Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
                     "after generate Mipmap, before Freeing SDL surface\n"
                    );

        SDL_FreeSurface(surface);
        glBindTexture(GL_TEXTURE_2D, 0);
    }




NAMESPACE_END