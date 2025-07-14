#include "misc.hh"
#include "Camera.hh"

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
        SDL_WINDOW_OPENGL );
    error = {SDL_GetError()};
    if(window == NULL){
        cout << "SDL_CreateWindow Error: " << endl;
    }
    if(error != ""){
        cout << "SDL set GL attribute Error: " << error << endl;
    }

    int flagjpg = IMG_INIT_JPG;
    if(!(IMG_Init(flagjpg) & flagjpg)){
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


int getGlInfo(){
    GLuint errorcode;
    GLint tmp;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &tmp);

    cout << "GL_MAX_VERTEX_ATTRIBS: " << tmp << endl;

    return errorcode;
}

bool processUserInput(SDL_Event& e, bool quit, glm::vec3 cameraPosition){

    return quit;
}

void render(SDL_Window* window, GLuint shaderProgram[], GLuint vaoTarget[], GLuint textureTarget[]){

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


        //init the matrixs
        glm::mat4 matrixIdentity = glm::mat4(1.0f);
        glm::mat4 matrixModel = glm::scale(matrixIdentity, glm::vec3(1.0f,1.0f,1.0f ));
        matrixModel = glm::translate(matrixModel, glm::vec3(0.0f, 0.0f, 0.0f));
//        matrixModel = glm::rotate(matrixModel, glm::radians( fmod((SDL_GetTicks64() / 10.0f), 360.0f)), glm::vec3(0.0f, 1.0f, 0.0f));


        int screenWidth, screenHeight;
        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
        glm::mat4 matrixProjection = glm::perspective(glm::radians(80.0f), float{screenWidth/screenHeight}, 0.1f, 100.0f);


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
        if(keystates[SDL_SCANCODE_W]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 0.0f, -1.0f));cout << "w pressed" << endl; }
        if(keystates[SDL_SCANCODE_S]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 0.0f, 1.0f)); cout << "s pressed" << endl; }
        if(keystates[SDL_SCANCODE_A]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(-1.0f, 0.0f, 0.0f)); cout << "a pressed" << endl; }
        if(keystates[SDL_SCANCODE_D]){     spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(1.0f, 0.0f, 0.0f)); cout << "d pressed" << endl;}
        if(keystates[SDL_SCANCODE_SPACE]){ spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)); cout << "space pressed" << endl;}
        if(keystates[SDL_SCANCODE_LCTRL]){ spaceCamera.syncCameraPositionData( deltaTime, glm::vec3(0.0f, -1.0f, 0.0f));cout << "ctrl pressed" << endl; }

        
        spaceCamera.syncCameraAngleData(voffset, hoffset, {0});
        spaceCamera.setCameraSpeed(cameraMoveSpeed);
        //spaceCamera.setCameraSensitivity()
        glm::mat4 matrixView = spaceCamera.updateCamera();

        float radiusRotate = 1.0f;
        glm::vec3 cubePositions[] = {
//            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3(radiusRotate * sin(float{ SDL_GetTicks64() / 1000.0f }), 
                      1.75, 
                      radiusRotate * cos(float{ SDL_GetTicks64() / 1000.0f }) ), 
//            glm::vec3( -2.0f,  0.0f, 0.0f),  
            glm::vec3(0.0f, 0.75, 0.0f),  
//            glm::vec3( 0.0f, -2.0f, 0.0f),  
//            glm::vec3( 0.0f,  0.0f, 2.0f),  
//            glm::vec3( 0.0f,  0.0f, -2.0f),  
//            glm::vec3( 1.5f,  2.0f, -2.5f), 
//            glm::vec3( 1.5f,  0.2f, -1.5f), 
//            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(shaderProgram[0]);

/*================================================*/
        //render floor
        glm::mat4 matrixFloorFlip = glm::scale(matrixIdentity, glm::vec3(3.0f, 3.0f, 3.0f));
        matrixFloorFlip = glm::rotate(matrixFloorFlip, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[0], "matrixModel"), 1, GL_FALSE, glm::value_ptr(matrixFloorFlip));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[0], "matrixView"), 1, GL_FALSE, glm::value_ptr(matrixView));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[0], "matrixProjection"), 1, GL_FALSE, glm::value_ptr(matrixProjection));

        #ifdef DEBUG
        errorposition(__FILE__, __LINE__);
        #endif

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureTarget[0]);
        glUniform1i(glGetUniformLocation(shaderProgram[0], "wallTexture"), 0);
        glBindVertexArray(vaoTarget[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        
        #ifdef DEBUG
        errorposition(__FILE__, __LINE__);
        #endif

        
/*================================================*/
        //render light
        glUseProgram(shaderProgram[1]);
        glm::mat4 matrixModelLight = glm::scale(glm::translate(matrixIdentity, cubePositions[0]), glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[1], "matrixModel"), 1, GL_FALSE, glm::value_ptr(matrixModelLight));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[1], "matrixView"), 1, GL_FALSE, glm::value_ptr(matrixView));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[1], "matrixProjection"), 1, GL_FALSE, glm::value_ptr(matrixProjection));
        glBindVertexArray(vaoTarget[1]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        
/*================================================*/
        //render cube
        glBindVertexArray(vaoTarget[2]);
        glm::mat4 offsetMatrix = glm::translate(matrixModel, cubePositions[1]);
        glm::mat3 matrixNormal = glm::transpose(glm::inverse(glm::mat3(offsetMatrix)));

        glUseProgram(shaderProgram[3]);
        //vertex shader uniform
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[3], "matrixModel"), 1, GL_FALSE, glm::value_ptr(offsetMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[3], "matrixView"), 1, GL_FALSE, glm::value_ptr(matrixView));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[3], "matrixProjection"), 1, GL_FALSE, glm::value_ptr(matrixProjection));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[3], "matrixNormal"), 1, GL_FALSE, glm::value_ptr(matrixNormal));

        //fragment shader uniform
        auto cameraPos = spaceCamera.getCameraPosition();
        //object material struct
        glUniform3f(glGetUniformLocation(shaderProgram[3], "material.v3fAmbient"), 0.0215f, 0.1745f, 0.0215f);
        glUniform1f(glGetUniformLocation(shaderProgram[3], "material.fAmbientCoeff"), 0.1f);
        glUniform3f(glGetUniformLocation(shaderProgram[3], "material.v3fDiffuse"), 0.07568f, 0.61424f, 0.07568f);
        glUniform1f(glGetUniformLocation(shaderProgram[3], "material.fDiffuseCoeff"), 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram[3], "material.v3fSpecular"), 0.633f, 0.727811f, 0.633f);
        glUniform1f(glGetUniformLocation(shaderProgram[3], "material.fSpecularCoeff"), 0.6f * 128.0f);

        //light struct
        glUniform3f(glGetUniformLocation(shaderProgram[3], "light.v3fAmbient"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram[3], "light.v3fDiffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram[3], "light.v3fSpecular"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram[3], "light.v3fPosition"), cubePositions[0].x, cubePositions[0].y, cubePositions[0].z);

        glUniform3f(glGetUniformLocation(shaderProgram[3], "v3fViewPos"), cameraPos.x, cameraPos.y, cameraPos.z);


        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, textureTarget[1]);
        glUniform1i(glGetUniformLocation(shaderProgram[3], "texture0"), 1);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        #ifdef DEBUG
        errorposition(__FILE__, __LINE__);
        #endif

        SDL_GL_SwapWindow(window);


    }
}

