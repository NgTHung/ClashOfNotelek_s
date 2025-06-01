#include "Event/EventQueue.hpp"

std::optional<std::shared_ptr<BaseEvent>> EventQueue::PopEvent()
{
    if (this->IsEmpty())
    {
        return std::nullopt;
    }
    std::shared_ptr<BaseEvent> TopEvent = std::move(m_Queue.front());
    m_Queue.pop();
    return TopEvent;
}

bool EventQueue::PushEvent(std::shared_ptr<BaseEvent> Event)
{
    this->m_Queue.push(std::move(Event));
    return true;
}

bool EventQueue::IsEmpty() const
{
    return this->m_Queue.empty();
}

size_t EventQueue::Size() const
{
    return this->m_Queue.size();
}