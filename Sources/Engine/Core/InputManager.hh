//
// Created by phage on 10/22/25.
//

#ifndef INPUTMANAGER_HH
#define INPUTMANAGER_HH


#include <Common.hh>
#include <SDL2/SDL.h>
#include <EventManager.hh>
NAMESPACE_BEGIN


//class InputManager {
//public:
//    InputManager(EventManager& eventMgr)
//        : eventManager(eventMgr) {}
//
//    bool isKeyHeld(SDL_Scancode key) const;
//    bool isMouseButtonHeld(Uint8 button) const;
//
//
//    void pollEvents();
//
//private:
//    EventManager& eventManager;
//};

class InputManager {
public:
    InputManager(EventManager& eventMgr): eventManager(eventMgr) {};

    // 每帧调用
    void pollEvents();

    // ✅ 状态查询接口
    bool isKeyHeld(SDL_Scancode key) const;
    bool isMouseButtonHeld(Uint8 button) const;

    int getMouseX() const { return mouseX; }
    int getMouseY() const { return mouseY; }
    int getMouseDeltaX() const { return mouseDeltaX; }
    int getMouseDeltaY() const { return mouseDeltaY; }

private:
    EventManager& eventManager;

    // 按键状态表
    std::unordered_map<SDL_Scancode, bool> keyStates;
    std::unordered_map<Uint8, bool> mouseStates;

    // 鼠标状态
    int mouseX = 0, mouseY = 0;
    int mouseDeltaX = 0, mouseDeltaY = 0;
};



NAMESPACE_END
#endif //INPUTMANAGER_HH
