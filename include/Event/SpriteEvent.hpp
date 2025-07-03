#pragma once
#include "Event.hpp"

enum class Direction;
class Character;

class CharacterMovedEvent: public BaseEvent {
private:
    Direction m_NewDirection;
    Character &m_Character;
public:
    GlobalEventType GetEventType() const override;
    CharacterMovedEvent(Character &Character, const Direction &NewDirection);
};

class CharacterStopMoved: public BaseEvent {
private:
    Direction m_OldDirection;
    Character &m_Character;
public:
    GlobalEventType GetEventType() const override;
    CharacterStopMoved(Character &Character, const Direction &OldDirection);
};

class CharacterAttackEvent: public BaseEvent {
private:
    Character &m_Character;
public:
    GlobalEventType GetEventType() const override;
    CharacterAttackEvent(Character &Character);
};