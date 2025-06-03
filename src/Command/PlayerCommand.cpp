#include "Command/PlayerCommand.hpp"

#include "Event/PlayerEvent.hpp"
#include "Graphic/Player.hpp"
#include "State/StartScreen.hpp"

MovePlayerCommand::MovePlayerCommand(Player &player, const Direction &NewDirection): m_Player(player), m_NewDirection(NewDirection) {};
void MovePlayerCommand::execute()
{
    m_Player.AddDirection(m_NewDirection);
    EventDispatcher::GetInstance().Dispatch(std::make_shared<PlayerMovedEvent>(m_Player, m_NewDirection));
}

StopPlayerMovingCommand::StopPlayerMovingCommand(Player &player, const Direction &OldDirection): m_Player(player), m_OldDirection(OldDirection) {};
void StopPlayerMovingCommand::execute()
{
    m_Player.RemoveDirection(m_OldDirection);
    EventDispatcher::GetInstance().Dispatch(std::make_shared<PlayerStopMoved>(m_Player, m_OldDirection));
}

AdvancePlayerIndexCommand::AdvancePlayerIndexCommand(Player &g_Player): m_Player(g_Player) {};
void AdvancePlayerIndexCommand::execute()
{
    m_Player.AdvanceIndex();
}