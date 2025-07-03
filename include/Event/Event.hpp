#pragma once
enum class GlobalEventType
{
    Generic,
    GameQuit,
    SaveGame,
    PlayerAction,
    PlayerMoved,
    PlayerStopMoved,
    PlayerAttacked,
    CharacterMoved,
    CharacterStopMoved,
    CharacterAttack
};

class BaseEvent
{
public:
    virtual ~BaseEvent() = default;
    virtual GlobalEventType GetEventType() const = 0;
};