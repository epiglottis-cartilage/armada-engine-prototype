#pragma once

#define DEFAULT_TEXTURE_NAME "defaulttexture.png"



#include <Common.hh>
#include <ConfigTypes.hh>
#include <Shader.hh>
#include <Texture.hh>
#include <Logger.hh>
#include <Camera.hh>
#include <Model.hh>
#include <ShaderManager.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

//coupling to ECS currently......but same as Ogre!
#include <StageManager.hh>
#include <AssetSystem.hh>

NAMESPACE_BEGIN

#define SHADERDIR "shaders"

struct RenderContext {
    Camera* aCurrentCamera;
    float deltatime;


};

struct RenderCommand {
    const Model* model;
    const Shader* shader;
    glm::mat4 transform;
    
};

class FLEET_API RenderSystem {


public:
    RenderSystem(cfgRenderSystem config, AssetSystem* assetManager);
    ~RenderSystem();

    /*if logger is on, this method report all OpenGL error to logger untill no error. 
    Noticed that currently this method always return 0*/
    int errorposition(
        const char* file=__FILE__,
         int line=__LINE__
    );

    void updatestatmanager(StateManager* stateManager);
    ShaderManager* getShaderManager() const { return shaderManager; }

    /*Noticed: this method will update the aCurrentCamera's viewmatrix field*/
    void prerender(RenderContext* context);
    void renderframe(RenderContext* context);
    void postrender(RenderContext* context);

    void initcamera(Camera* camera) {
//        this->shaderManager->bindUBO(camera);
    }

private:
    void init();
    void parseconfig(cfgRenderSystem config);

    /*submit a render request on model, using model's transform*/
    void submit(const Model* model, const Shader* shader);
    /*submit a render request on model, using the transform in parameter*/
    void submit(const Model* model, const Shader* shader, const glm::mat4& transform);
    void executecommand(const RenderCommand& command);

    void drawmesh(const Model::Mesh& mesh, const Shader& shader, const glm::mat4& transform) const;
    void drawmodel(const Model& model, const Shader& shader, const glm::mat4& transform) const;

    cfgRenderSystem config;
    AssetSystem* assetManagerPtr;

    int windowWidth;
    int windowHeight;
    int windowFlags;
    bool vsync_on;
    int sdl_image_flags;

    
    SDL_Window* window;
    //SDL_GLContext is already void* pointer.......although I hate such usage
    SDL_GLContext glContext;

    StateManager* stateManager;
    ShaderManager* shaderManager;

    vector<RenderCommand> cmdQueue;


    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 modelMatrix;
};






NAMESPACE_END