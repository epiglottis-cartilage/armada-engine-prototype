#ifndef MISC_HH
#define MISC_HH
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <modelloader.hh>
#include <Camera.hh>



SDL_Window* init_win_and_gl();

int programExit(SDL_Window* window);

int getGlInfo();

void render(SDL_Window* window, vector<ShaderFinal> stlShaderList, vector<Model> stlModelList);

GLenum errorposition(const char* file, int line);







#endif