//
// Created by phage on 10/22/25.
//

#include "EventManager.hh"

NAMESPACE_BEGIN

EventSubscriber EventManager::subscribe(EventType type, Callback callback) {
    EventSubscriber subscriber(type, callback);
    subscriber.idSubscriber = idSubscribers++;
    //implicit creation of a full null subscriber here!
    subscribers[type][subscriber.idSubscriber] = subscriber;
    return subscriber;
}

void EventManager::publish(const Event& event) {
    auto& subs_list = subscribers[event.getType()];
    for (auto& subs : subs_list){
         subs.second.functionCallback(event);
    }
}

void EventManager::unsubscribe(EventSubscriber subscriber) {
    subscribers[subscriber.typeSubscribe].erase(subscriber.idSubscriber);
}

NAMESPACE_END