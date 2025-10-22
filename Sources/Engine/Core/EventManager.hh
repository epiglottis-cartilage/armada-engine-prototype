//
// Created by phage on 10/22/25.
//

#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH

#include <atomic>
#include <unordered_map>
#include <functional>

#include <Common.hh>
#include <Event.hh>

NAMESPACE_BEGIN

using Callback = std::function<void(const Event&)>;

class EventManager;

class FLEET_API EventSubscriber {

    friend class EventManager;

public:
    EventSubscriber() = default;
    EventSubscriber(EventType type, Callback callback) : typeSubscribe(type), functionCallback(callback) {}
    EventType typeSubscribe;
    Callback functionCallback;
    int getID() const {return this->idSubscriber;};
private:
    int idSubscriber;
};

class FLEET_API EventManager {
public:

    EventSubscriber subscribe(EventType type, Callback callback);

    // 触发事件
    void publish(const Event& event);

    void unsubscribe(EventSubscriber subscriber);

    // 清空订阅（例如在系统退出时）
    void clear() {
        subscribers.clear();
    }

private:
    std::unordered_map<EventType, std::unordered_map<int , EventSubscriber>> subscribers;
    std::atomic<int> idSubscribers {0};
};


NAMESPACE_END


#endif //EVENTMANAGER_HH
