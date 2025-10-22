//
// Created by phage on 10/22/25.
//

#include "InputManager.hh"
#include <imgui_impl_sdl2.h>
#include <GlobalContext.hh>

NAMESPACE_BEGIN
extern AppContext* objptrAppContext;
    //void InputManager::pollEvents() {
//    SDL_Event e;
//    while (SDL_PollEvent(&e)) {
//        switch (e.type) {
//        case SDL_QUIT:
//            eventManager.publish(QuitEvent());
//            break;
//
//        case SDL_KEYDOWN:
//            eventManager.publish(KeyPressedEvent(e.key.keysym.sym));
//            break;
//
//        case SDL_KEYUP:
//            eventManager.publish(KeyReleasedEvent(e.key.keysym.sym));
//            break;
//
//        case SDL_MOUSEMOTION:
//            eventManager.publish(MouseMovedEvent(e.motion.x, e.motion.y));
//            break;
//
//        default:
//            break;
//        }
//    }
//}

void InputManager::pollEvents() {
    // 每帧重置鼠标移动量
    mouseDeltaX = mouseDeltaY = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //IMGUI poll event goes first
        ImGui_ImplSDL2_ProcessEvent(&e);

        switch (e.type) {
        case SDL_QUIT:
            eventManager.publish(QuitEvent(e));
            break;

        case SDL_KEYDOWN:
            if (!e.key.repeat) { // 防止系统级重复事件
                keyStates[e.key.keysym.scancode] = true;
                eventManager.publish(KeyPressedEvent(e.key.keysym.sym));
            }
            break;

        case SDL_KEYUP:
            keyStates[e.key.keysym.scancode] = false;
            eventManager.publish(KeyReleasedEvent(e.key.keysym.sym));
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseStates[e.button.button] = true;
//            eventManager.publish(MouseButtonPressedEvent(e.button.button));
            break;

        case SDL_MOUSEBUTTONUP:
            mouseStates[e.button.button] = false;
//            eventManager.publish(MouseButtonReleasedEvent(e.button.button));
            break;

        case SDL_MOUSEMOTION:
            if (objptrAppContext->aEditorMode)
                break;
            mouseDeltaX = e.motion.xrel;
            mouseDeltaY = e.motion.yrel;
            mouseX = e.motion.x;
            mouseY = e.motion.y;
            eventManager.publish(MouseMovedEvent(e.motion.x, e.motion.y));
            break;

        default:
            break;
        }
    }

    // 同步 SDL 键盘状态（用于 hold 检查）
    const Uint8* sdlKeys = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        keyStates[(SDL_Scancode)i] = sdlKeys[i];
    }

    // 鼠标状态同步
    Uint32 buttons = SDL_GetMouseState(nullptr, nullptr);
    mouseStates[SDL_BUTTON_LEFT]   = buttons & SDL_BUTTON_LMASK;
    mouseStates[SDL_BUTTON_RIGHT]  = buttons & SDL_BUTTON_RMASK;
    mouseStates[SDL_BUTTON_MIDDLE] = buttons & SDL_BUTTON_MMASK;
}

bool InputManager::isKeyHeld(SDL_Scancode key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputManager::isMouseButtonHeld(Uint8 button) const {
    auto it = mouseStates.find(button);
    return it != mouseStates.end() && it->second;
}




NAMESPACE_END