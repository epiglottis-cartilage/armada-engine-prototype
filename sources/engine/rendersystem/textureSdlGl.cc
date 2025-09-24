#include "texturesdlgl.hh"

TextureSdlGl::TextureSdlGl(string filepathTexture) {
        SDL_Surface *surface = IMG_Load(filepathTexture.c_str());
        if(surface == NULL){
            std::cout << "Creating SDL_Surface from filepath Error: " << IMG_GetError() << std::endl;
        }

        //safely force convert into rgba32 format under sdl_surface
        surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        if (surface == NULL){
            std::cout << "Safely convert raw SDL_Surface into rgba32 SDL_Surface Error: " << SDL_GetError() << std::endl;
        }
            

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        #ifdef DEBUG 
        std::cout << "Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
        "After load an image as SDL_Surface and before convert it to GL texture"
        << std::endl;
        #endif
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
        #ifdef DEBUG 
        std::cout << "Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
        "After convert SDL surface to GL texture"
        "if you see this, it means SDL_Surface has been successfully converted to GL texture"
        << std::endl;
        #endif

        GLenum errorClass;
        while((errorClass = glGetError()) != GL_NO_ERROR){
            std::cout << "SDL surface to GL texture Error: " << errorClass << std::endl;
        }

        glGenerateMipmap(GL_TEXTURE_2D);


        while((errorClass = glGetError()) != GL_NO_ERROR){
            std::cout << "GL generate Mipmap Error: " << errorClass << std::endl;
        }

        #ifdef DEBUG 
        std::cout << "Current Exec Pos: Inside TextureSdlGl::TextureSdlGl(string filepathTexture)"
        "after generate Mipmap, before Freeing SDL surface"
        << std::endl;
        #endif
        SDL_FreeSurface(surface);
        glBindTexture(GL_TEXTURE_2D, 0);
    }








