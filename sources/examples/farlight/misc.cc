#include "misc.hh"

#define WINDOW_WIDTH 1920
#define WINDOW_HIGHT 1080


using namespace std;

GLenum errorposition(const char* file, int line){

    GLenum errorcode;
    while ((errorcode = glGetError()) != GL_NO_ERROR) 
    {
        cout << "Error: " << errorcode << " at " << file << ":" << line << endl;
    }
    return errorcode;
}

SDL_Window* init_win_and_gl(){

    SDL_GLContext gContext;
    GLuint errorcode;
    GLenum errorClass;
    SDL_Init(SDL_INIT_EVERYTHING);
    string error = {SDL_GetError()};
    if(error != ""){
        cout << "SDL_Init Error: " << error << endl;
    }


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    error = {SDL_GetError()};
    if(error != ""){
        cout << "SDL set GL attribute Error: " << error << endl;
    }


    SDL_Window* window = SDL_CreateWindow("get gl info", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HIGHT,  
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE );
    error = {SDL_GetError()};
    if(window == NULL){
        cout << "SDL_CreateWindow Error: " << endl;
    }
    if(error != ""){
        cout << "SDL set GL attribute Error: " << error << endl;
    }

    int flagjpg = IMG_INIT_JPG;
    int flagpng = IMG_INIT_PNG;
    //if(!(IMG_Init(flagjpg) & flagjpg)){
    auto img_init_result = IMG_Init(flagpng);

    if(img_init_result != flagpng){
        cout << img_init_result << endl;
        error = {IMG_GetError()};
        cout << "IMG_Init Error: " << error << endl;
    }

    gContext = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;

    glewInit();
    glGetError();

    int windowwidth, windowheight;
    SDL_GetWindowSize(window, &windowwidth, &windowheight);

    glViewport(0, 0, windowwidth, windowheight);

    SDL_GL_SetSwapInterval(1);

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

    return window;
}

int programExit(SDL_Window* window){
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void render(SDL_Window* window, vector<ShaderFinal> stlShaderList, vector<Model> stlModelList){

    bool quit = false;
    SDL_Event e;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    uint64_t lastFrameTime{0}, currentFrameTime{0};
    float cameraMoveSpeed{1.0f}, deltaTime{0.0f};//s
    float hoffset{0}, voffset(0);

    Camera spaceCamera = Camera(cameraPosition);

    while(quit == false){
        currentFrameTime = SDL_GetTicks64();
        deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;


        int screenWidth, screenHeight;
        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
        float screenRatio = static_cast<float>(screenWidth / screenHeight);

        //init the matrixs
        glm::mat4 matrixIdentity = glm::mat4(1.0f);
        glm::mat4 matrixModel = glm::scale(matrixIdentity, glm::vec3(1.0f,1.0f,1.0f ));
        matrixModel = glm::translate(matrixModel, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 matrixProjection = glm::perspective(glm::radians(80.0f), screenRatio, 0.1f, 100.0f);


        //process user input
        while(SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:

                    switch (e.window.event) {

                        case SDL_WINDOWEVENT_CLOSE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;

                //deal with key press
                case SDL_KEYDOWN:

                    // deal according to keysymcode
                    switch (e.key.keysym.sym) {

                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                        case SDLK_UP:
                            //offsetTransparent += 0.1f;
                            cameraMoveSpeed += 0.1f;
                            break;
                        case SDLK_DOWN:
                            //offsetTransparent -= 0.1f;
                            cameraMoveSpeed -= 0.1f;
                            break;

                        
                        default:
                            break;
                    }
                    break;

                /*
                 * in SDL mouse relative mode, mouse move right = x positive offset, mouse move down = y positive offset 
                */
                case SDL_MOUSEMOTION:
                    hoffset = e.motion.xrel , 
                            voffset = -e.motion.yrel ;
                    break;

                //anything else
                default:
                    break;
            }
        }


        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 0.0f, -1.0f)); }
        if(keystates[SDL_SCANCODE_S]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));  }
        if(keystates[SDL_SCANCODE_A]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(-1.0f, 0.0f, 0.0f));; }
        if(keystates[SDL_SCANCODE_D]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(1.0f, 0.0f, 0.0f)); }
        if(keystates[SDL_SCANCODE_SPACE]){ spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)); }
        if(keystates[SDL_SCANCODE_LCTRL]){ spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, -1.0f, 0.0f));}

        
        spaceCamera.syncCameraAngleData(voffset, hoffset, {0});
        spaceCamera.setCameraSpeed(cameraMoveSpeed);
        //spaceCamera.setCameraSensitivity()
        glm::mat4 matrixView = spaceCamera.updateCamera();


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (int i = 0; i < stlModelList.size(); i++) {
            stlModelList[i].Draw(stlShaderList[0]);
        }
        


        #ifdef DEBUG
        errorposition(__FILE__, __LINE__);
        #endif

        SDL_GL_SwapWindow(window);


    }
}

