#pragma once
#include <Common.hh>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

NAMESPACE_BEGIN

class AppContext;

class UIDrawSystem {


public:
    UIDrawSystem();

    ~UIDrawSystem(){
        this->quit();
    }


    void prerender();

    void drawframe();

    void postrender();



private:
    void init(SDL_Window* window, SDL_GLContext glcontext);
    void quit();


};

NAMESPACE_END