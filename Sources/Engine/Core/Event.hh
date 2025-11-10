//
// Created by phage on 10/22/25.
//

#ifndef EVENT_HH
#define EVENT_HH

#include <Common.hh>
#include <SDL2/SDL.h>

NAMESPACE_BEGIN

//normally this should print all vals, but....i am lazy with that.
//if engine user need some other event, they need a little hacking into engine
enum class EventType {
    General,
    WindowResizeEvent,
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    Quit

    //further extension can be put here....not sure if this is good design
};

// 所有事件的基类
struct Event {
public:
    SDL_Event rawevent;
    Event() = default;
    Event(SDL_Event e) : rawevent(e) {};
    virtual ~Event() = default;
    virtual EventType getType() const {return EventType::General;};
};

struct WindowResizedEvent : public Event {
    int width, height;
    WindowResizedEvent(int w,int h) : width(w), height(h) {}
    EventType getType() const override { return EventType::WindowResizeEvent; }
};

struct MouseButtonPressedEvent : public Event {
    int x, y;
    MouseButtonPressedEvent(int mx, int my) : x(mx), y(my) {}
    EventType getType() const override { return EventType::MouseButtonPressed; }
};

struct MouseButtonReleasedEvent : public Event {
    int x, y;
    MouseButtonReleasedEvent(int mx, int my) : x(mx), y(my) {}
    EventType getType() const override { return EventType::MouseButtonReleased; }
};

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
