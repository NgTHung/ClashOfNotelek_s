#pragma once
enum class GlobalEventType
{
    Generic,
    GameQuit,
    SaveGame,
    PlayerAction,
    PlayerMoved,
    PlayerStopMoved,
    PlayerAttacked
};

class BaseEvent
{
public:
    virtual ~BaseEvent() = default;
    virtual const GlobalEventType GetEventType() const = 0;
};