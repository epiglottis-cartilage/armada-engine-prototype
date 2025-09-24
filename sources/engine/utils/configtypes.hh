#pragma once
#include <string>

struct cfgRenderSystem {
    int screenwidth = 1280;
    int screenheight = 720;
    std::string screenmode = "window";
    bool vsync = false;
    int antialiasing = 0;
    int shadowquality = 0;

    std::string sdlimg_format = "png";
};

struct cfgAssetSystem {
    std::string assetpath = "";

};

struct cfgAppContext {
    bool debugmode = false;
};

struct cfgAudioSystem {
    bool placeholder = false;

};

struct cfgInputSystem {
    bool placeholder = false;
};

struct cfgPhysicsSystem {
    bool placeholder = false;
};