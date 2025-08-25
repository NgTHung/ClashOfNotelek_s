#include "Event/EventDispatcher.hpp"

#include "Utility/Logger.hpp"

void EventDispatcher::Dispatch(const std::shared_ptr<BaseEvent> &Event)
{
    if (!Event)
    {
        LOG_ERROR("Event is null");
        return;
    }
    GlobalEventType Type = Event->GetEventType();
    LOG_DEBUG("Dispatch event type: {}", static_cast<int>(Type));
    if (m_Listeners.contains(Type))
    {
        bool selfUnregistered = false;
        for (auto &Listener : m_Listeners[Type])
        {
            if (Listener)
            {
                if (Listener(Event))
                {
                    Listener = nullptr;
                    LOG_DEBUG("Listener for event type {} self-unregister.", static_cast<int>(Type));
                    selfUnregistered = true;
                }
            }
        }
        if (selfUnregistered)
        {
            // Remove null listeners
            std::erase(m_Listeners[Type], nullptr);
        }
    }
}

void EventDispatcher::RegisterListener(GlobalEventType Type, const EventListener &Listener)
{
    if (Listener)
    {
        m_Listeners[Type].push_back(Listener);
        LOG_DEBUG("Registered listener for event type: {}", static_cast<int>(Type));
    }
    else
    {
        LOG_ERROR("Attempted to register a null listener for event type: {}", static_cast<int>(Type));
    }
}

EventDispatcher &EventDispatcher:: GetInstance()
{
    static EventDispatcher instance;
    return instance;
}

void EventDispatcher::UnRegisterListener(GlobalEventType Type, const EventListener &Listener)
{
    if (m_Listeners.contains(Type))
    {
        auto &ListenerAtType = m_Listeners[Type];
        std::erase_if(ListenerAtType, [&Listener](const EventListener &registeredListener)
                      {
            if (!Listener) {
                return !registeredListener;
            }
            if (!registeredListener) {
                return true;
            }
            return registeredListener.target_type() == Listener.target_type() && registeredListener.target<bool()>() == Listener.target<bool()>(); });
    }
    else
    {
        LOG_WARNING("No listeners registered for event type: {}", static_cast<int>(Type));
    }
}

void EventDispatcher::UnRegisterAllListeners(GlobalEventType Type)
{
    if (m_Listeners.contains(Type))
    {
        m_Listeners[Type].clear();
        LOG_DEBUG("Unregistered all listeners for event type: {}", static_cast<int>(Type));
    }
    else
    {
        LOG_WARNING("No listeners registered for event type: {}", static_cast<int>(Type));
    }
}

void EventDispatcher::UnRegisterAllListeners()
{
    m_Listeners.clear();
    LOG_DEBUG("Unregistered all listeners for all event types.");
}