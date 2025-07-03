#include "Event/SpriteEvent.hpp"

CharacterMovedEvent::CharacterMovedEvent(Character &Character, const Direction &NewDirection) : m_NewDirection(NewDirection), m_Character(Character) {};
GlobalEventType CharacterMovedEvent::GetEventType() const
{
    return GlobalEventType::CharacterMoved;
}

CharacterStopMoved::CharacterStopMoved(Character &Character, const Direction &OldDirection) : m_OldDirection(OldDirection), m_Character(Character) {};
GlobalEventType CharacterStopMoved::GetEventType() const
{
    return GlobalEventType::CharacterStopMoved;
}

CharacterAttackEvent::CharacterAttackEvent(Character& Character):m_Character(Character){}

GlobalEventType CharacterAttackEvent::GetEventType() const
{
    return GlobalEventType::CharacterAttack;
}