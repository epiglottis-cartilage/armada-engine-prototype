#include <RenderSystem.hh>

NAMESPACE_BEGIN


RenderSystem::RenderSystem(cfgRenderSystem config, AssetSystem* assetManager)
{
    this->parseconfig(config);
    this->assetManagerPtr = assetManager;
    //init will use asset manager inside!
    this->init();
}

void RenderSystem::parseconfig(cfgRenderSystem config){
    this->config = config;

    if(config.screenmode == "window"){
        this->windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    }else if(config.screenmode == "fullscreen"){
        this->windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
    }

    if(config.vsync){
        this->vsync_on = true;
    }else {
        this->vsync_on = false;
    }

    this->windowWidth = config.screenwidth;
    this->windowHeight = config.screenheight;

//    if(config.sdlimg_format == "png"){
//        this->sdl_image_flags = IMG_INIT_PNG;
//    }
//    if(config.sdlimg_format == "jpg"){
//        this->sdl_image_flags = IMG_INIT_JPG;
//    }
    this->sdl_image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP  ;


}

/*On run, a RenderSystem will implicitly create a ShaderManager on init()*/
void RenderSystem::init(){
    GLuint errorcode;
    GLenum errorClass;
    SDL_Init(SDL_INIT_EVERYTHING);
    string error = {SDL_GetError()};
    if(error != ""){
        ENGINE_ERROR("SDL_Init Error: %s\n", error);
    }


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    error = {SDL_GetError()};
    if(error != ""){
        ENGINE_ERROR("SDL set GL attribute Error:{}", error);
    }

    string windowtitle = objptrAppContext->aGamename + " " + objptrAppContext->aGameVersion;
    this->window = SDL_CreateWindow(windowtitle.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        this->windowWidth, 
        this->windowHeight,  
        this->windowFlags 
    );
    error = {SDL_GetError()};
    objptrAppContext->aRenderContext->mainwindow = this->window;
    if(window == NULL){
        ENGINE_ERROR("SDL_CreateWindow Error: {}", error);
    }
    
    if(error != ""){
        ENGINE_ERROR("SDL set GL attribute Error: {}", error);
    }

    auto img_init_result = IMG_Init(this->sdl_image_flags);

    if(img_init_result != this->sdl_image_flags){
        ENGINE_DEBUG("{}\n",img_init_result);
        cout << img_init_result << endl;
        error = {IMG_GetError()};
        ENGINE_ERROR("IMG_Init Error: {}\n", error);
    }

    this->glContext = SDL_GL_CreateContext(window);
    objptrAppContext->aRenderContext->glcontext = this->glContext;
    glewExperimental = GL_TRUE;

    glewInit();
    initGLDebug();
    glGetError();

    int windowwidth, windowheight;
    SDL_GetWindowSize(window, &windowwidth, &windowheight);

    glViewport(0, 0, windowwidth, windowheight);

    int vsync = this->vsync_on ? 1 : 0;
    SDL_GL_SetSwapInterval(vsync);

    glEnable(GL_DEPTH_TEST);

    ENGINE_INFO("code execute to init_win_and_gl end");
    while((errorClass = glGetError()) != GL_NO_ERROR){
        ENGINE_ERROR("GL error occur! Error code: {}", errorClass);
    }
    error = {SDL_GetError()};
    if(error != ""){
        ENGINE_ERROR("SDL set GL attribute Error: {}", error);
    }

    ENGINE_INFO("RENDER SYSTEM INIT COMPLETE");
    ENGINE_INFO("GL VERSION: {}", string{reinterpret_cast<const char*>(glGetString(GL_VERSION))});
    ENGINE_INFO("GLSL VERSION: {}", string{reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))});

    ENGINE_INFO("Register Phong Shader to ShaderFactory");
    ShaderFactory::init(this->assetManagerPtr->getShaderDir() );
    ENGINE_INFO("Creating ShaderManager...");
    this->shaderManager = new ShaderManager{};

    //experiment zone:
//    glEnable(GL_CULL_FACE);

    auto vender = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    auto renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    ENGINE_DEBUG("GL_VENDOR-GL_RENDERER-GL_VERSION: {} {} {}", vender, renderer, version);
}

RenderSystem::~RenderSystem(){
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}



//Rendering Command System
void RenderSystem::submit(const Model* model, const Shader* shader, const glm::mat4& transform){
//    if(!model->getShown()){
//        return;
//    }
    RenderCommand cmd{model, shader, transform};
    this->cmdQueue.push_back(cmd);
}


void RenderSystem::executecommand(const RenderCommand& cmd){
    this->drawmodel(*cmd.model, *cmd.shader, cmd.transform);
}


void RenderSystem::prerender(RenderContext* context){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera* camera = context->aCurrentCamera;
    CameraMatrices matCameraData = {camera->getViewMatrix(), camera->getProjectionMatrix(), camera->getCameraPosition()};
    //gltransform the camera matrix
    glBindBuffer(GL_UNIFORM_BUFFER, objptrAppContext->aRenderContext->uboBindings[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(matCameraData), &matCameraData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);


    //gltransform the transform matrix
//    auto rendertargets = this->stateManager->getEntities();
//    for(const auto& rendertarget: rendertargets){
//        auto model = rendertarget.second->getModel();
//        submit(model, model->getShader(), rendertarget.second->getTransform());
//    }
    auto& rendertargetsref = context->drawtargets;
    for (const auto& eachcommands: rendertargetsref)
    {
        submit(eachcommands.model, eachcommands.shader, eachcommands.transform);
    }
    //remember to clean the render context
    context->drawtargets.clear();
}

void RenderSystem::renderframe(RenderContext* context){
    for(RenderCommand& cmd: this->cmdQueue){
        //executing Render Command
        this->executecommand(cmd);
    }
    //clear rendering command
    this->cmdQueue.clear();
}

void RenderSystem::postrender(RenderContext* context){
    SDL_GL_SwapWindow(this->window);
}

//Processing rendering command


/*This method implicitly active the shader in second params,
transform the transform matrix in third parm to the active shader,
and then run gl drawcalls*/
void RenderSystem::drawmodel(const Model& model, const Shader& shader, const glm::mat4& transform) const{
    for (const auto& eachmesh: model.getMeshes()) {
        for (auto& prim: eachmesh.primitives) {
            prim.drawPrimitive(shader, transform * eachmesh.localtransform, &model);
        }
    }
}

NAMESPACE_END





