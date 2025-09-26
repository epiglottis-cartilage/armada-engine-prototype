#pragma once

#define DEFAULT_TEXTURE_NAME "defaulttexture.png"



#include <Common.hh>
#include <Model.hh>
#include <ConfigTypes.hh>
#include <Shader.hh>
#include <Texture.hh>
#include <Logger.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>


NAMESPACE_BEGIN

struct RenderCommand {
    const Model* model;
    const ShaderFinal* shader;
    glm::mat4 transform;
    
};

class FLEET_API RenderSystem {


public:
    RenderSystem(cfgRenderSystem config);
    ~RenderSystem();

    int errorposition(const char* file, int line);

    /*submit a render request on model, using model's transform*/
    void submit(const Model* model, const ShaderFinal* shader);
    /*submit a render request on model, using the transform in parameter*/
    void submit(const Model* model, const ShaderFinal* shader, const glm::mat4& transform);
    void renderframe();



private:
    void init();
    void parseconfig(cfgRenderSystem config);

    void executecommand(const RenderCommand& command);

    cfgRenderSystem config;

    int windowWidth;
    int windowHeight;
    int windowFlags;
    bool vsync_on;
    int sdl_image_flags;

    SDL_Window* window;
    //SDL_GLContext is already void* pointer.......although I hate such usage
    SDL_GLContext glContext;


    vector<RenderCommand> cmdQueue;


    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 modelMatrix;
    


};






NAMESPACE_END