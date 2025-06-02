#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Event.hpp"

class EventDispatcher {
public:
    typedef std::function<bool(std::shared_ptr<BaseEvent>)> EventListener;
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;
    static EventDispatcher& GetInstance();
    void Dispatch(const std::shared_ptr<BaseEvent>& Event);
    void RegisterListener(GlobalEventType Type, const EventListener &Listener);
    void UnRegisterListener(GlobalEventType Type, const EventListener &Listener);
    void UnRegisterAllListeners(GlobalEventType Type);
    void UnRegisterAllListeners();
private:
    EventDispatcher() = default;
    ~EventDispatcher() = default;
    std::unordered_map<GlobalEventType,std::vector<EventListener>> m_Listeners;
};
