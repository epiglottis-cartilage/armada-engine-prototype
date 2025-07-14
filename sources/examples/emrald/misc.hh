#ifndef MISC_HH
#define MISC_HH
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>



SDL_Window* init_win_and_gl();

int programExit(SDL_Window* window);

int getGlInfo();

bool processUserInput(SDL_Event& e, bool quit);

GLenum errorposition(const char* file, int line);

void render(SDL_Window* window, GLuint shaderProgram[], GLuint vaoTarget[], GLuint textureTarget[]);






#endif