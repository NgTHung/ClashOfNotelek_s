#pragma once
#include "Event/Event.hpp"
#include <queue>
#include <memory>
#include <optional>

class EventQueue
{
private:
    std::queue<std::shared_ptr<BaseEvent>> m_Queue;

public:
    EventQueue() = default;
    std::optional<std::shared_ptr<BaseEvent>> PopEvent();
    bool PushEvent(std::shared_ptr<BaseEvent> EnQueueEvent);
    template <typename T, typename... Args>
    bool PushEvent(Args &&...args);

    bool IsEmpty() const;
    size_t Size() const;
};

template <typename T, typename... Args>
bool EventQueue::PushEvent(Args &&...args)
{
    return PushEvent(std::make_shared<T>(std::forward<Args>(args)...));
}
