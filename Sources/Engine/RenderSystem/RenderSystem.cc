#include <RenderSystem.hh>

NAMESPACE_BEGIN

RenderSystem::RenderSystem(cfgRenderSystem config)
{
    this->parseconfig(config);
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

    if(config.sdlimg_format == "png"){
        this->sdl_image_flags = IMG_INIT_PNG;
    }else if(config.sdlimg_format == "jpg"){
        this->sdl_image_flags = IMG_INIT_JPG;
    }
}

void RenderSystem::init(){


//    this->glContext = new SDL_GLContext ;
    GLuint errorcode;
    GLenum errorClass;
    SDL_Init(SDL_INIT_EVERYTHING);
    string error = {SDL_GetError()};
    if(error != ""){
        ENGINE_ERROR("SDL_Init Error: %s\n", error);
    }


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    error = {SDL_GetError()};
    if(error != ""){
        ENGINE_ERROR("SDL set GL attribute Error: %s\n", error);
    }


    this->window = SDL_CreateWindow("get gl info", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        this->windowWidth, 
        this->windowHeight,  
        this->windowFlags 
    );
    error = {SDL_GetError()};
    if(window == NULL){
        ENGINE_ERROR("SDL_CreateWindow Error: \n", error);
    }
    if(error != ""){
        ENGINE_ERROR("SDL set GL attribute Error: \n", error);
    }

    auto img_init_result = IMG_Init(this->sdl_image_flags);

    if(img_init_result != this->sdl_image_flags){
        ENGINE_DEBUG("%d\n",img_init_result);
        cout << img_init_result << endl;
        error = {IMG_GetError()};
        ENGINE_ERROR("IMG_Init Error: %s\n", error);
    }

    this->glContext = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;

    glewInit();
    glGetError();

    int windowwidth, windowheight;
    SDL_GetWindowSize(window, &windowwidth, &windowheight);

    glViewport(0, 0, windowwidth, windowheight);

    int vsync = this->vsync_on ? 1 : 0;
    SDL_GL_SetSwapInterval(vsync);

    glEnable(GL_DEPTH_TEST);

    #ifdef DEBUG
    cout << "code execute to init_win_and_gl end" <<endl;
    while((errorClass = glGetError()) != GL_NO_ERROR){
        cout << "errorClass: " << errorClass << endl;
    }
    error = {SDL_GetError()};
    if(error != ""){
        cout << "SDL generate GL context or GL init Error: " << error << endl;
    }
    #endif
}

RenderSystem::~RenderSystem(){
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

int RenderSystem::errorposition(const char* file, int line){

    GLenum errorcode;
    while ((errorcode = glGetError()) != GL_NO_ERROR) 
    {
        ENGINE_ERROR("Error: %u at %s:%s\n", errorcode, file, line);
    }
    return static_cast<int>(errorcode);

}



//Rendering Command System
void RenderSystem::submit(const Model* model, const ShaderFinal* shader){
    if(!model->getShown()){
        return;
    }
    RenderCommand cmd{model, shader, model->getTransform()};
    this->cmdQueue.push_back(cmd);
}
void RenderSystem::submit(const Model* model, const ShaderFinal* shader, const glm::mat4& transform){
    if(!model->getShown()){
        return;
    }
    RenderCommand cmd{model, shader, transform};
    this->cmdQueue.push_back(cmd);
}



void RenderSystem::executecommand(const RenderCommand& cmd){
    cmd.model->Draw(*cmd.shader);
}



//Processing rendering command
void RenderSystem::renderframe(){
    for(RenderCommand cmd: this->cmdQueue){
        //executing Render Command
        this->executecommand(cmd);
    }
    //clear rendering command
    this->cmdQueue.clear();
}




NAMESPACE_END





