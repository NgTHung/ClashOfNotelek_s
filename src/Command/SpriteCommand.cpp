#include "Command/SpriteCommand.hpp"

#include "Event/SpriteEvent.hpp"
#include "Graphic/Sprite.hpp"
#include "State/HomeScreen.hpp"

MoveCharacterCommand::MoveCharacterCommand(Character &Character, const Direction &NewDirection)
    : m_Character(Character), m_NewDirection(NewDirection) {}
void MoveCharacterCommand::execute(){
    m_Character.AddDirection(m_NewDirection);
    EventDispatcher::GetInstance().Dispatch(std::make_shared<CharacterMovedEvent>(m_Character, m_NewDirection));
}
StopCharacterMovingCommand::StopCharacterMovingCommand(Character &Character, const Direction &OldDirection)
    : m_Character(Character), m_OldDirection(OldDirection) {}
void StopCharacterMovingCommand::execute() {
   m_Character.RemoveDirection(m_OldDirection);
   EventDispatcher::GetInstance().Dispatch(std::make_shared<CharacterStopMoved>(m_Character, m_OldDirection));
}    

CharacterAttackCommand::CharacterAttackCommand(Character& g_Character): m_Character(g_Character){}

void CharacterAttackCommand::execute(){
    m_Character.GetWeapon().Attack();
   EventDispatcher::GetInstance().Dispatch(std::make_shared<CharacterAttackEvent>(m_Character));
}