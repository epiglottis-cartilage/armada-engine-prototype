//
// Created by phage on 10/22/25.
//

#ifndef EVENT_HH
#define EVENT_HH

#include <Common.hh>
#include <SDL2/SDL.h>

NAMESPACE_BEGIN

enum class EventType {
    None,
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    Quit

    //further extension can be put here....not sure if this is good design
};

struct Event {
public:
    SDL_Event rawevent;
    Event() = default;
    Event(SDL_Event e) : rawevent(e) {};
    virtual ~Event() = default;
    virtual EventType getType() const {return EventType::None;};
};

//so....struct can inherit from a ......class?????
// 所有事件的基类

// 各种具体事件类型
struct KeyPressedEvent : public Event {
    SDL_Keycode key;
    KeyPressedEvent(SDL_Keycode k) : key(k) {}
    EventType getType() const override { return EventType::KeyPressed; }
};

struct KeyReleasedEvent : public Event {
    SDL_Keycode key;
    KeyReleasedEvent(SDL_Keycode k) : key(k) {}
    EventType getType() const override { return EventType::KeyReleased; }
};

struct MouseMovedEvent : public Event {
    int x, y;
    MouseMovedEvent(int mx, int my) : x(mx), y(my) {}
    EventType getType() const override { return EventType::MouseMoved; }
};

struct QuitEvent : public Event {
    QuitEvent(SDL_Event event) : Event(event) {}
    EventType getType() const override { return EventType::Quit; }
};

NAMESPACE_END

#endif //EVENT_HH
