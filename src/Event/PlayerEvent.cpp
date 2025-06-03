#include "Event/PlayerEvent.hpp"

PlayerMovedEvent::PlayerMovedEvent(Player &Player, const Direction &NewDirection):
    m_NewDirection(NewDirection), m_Player(Player) {};
const GlobalEventType PlayerMovedEvent::GetEventType() const {
    return GlobalEventType::PlayerMoved;
}

PlayerStopMoved::PlayerStopMoved(Player &Player, const Direction &OldDirection):
    m_OldDirection(OldDirection), m_Player(Player) {};
const GlobalEventType PlayerStopMoved::GetEventType() const {
    return GlobalEventType::PlayerStopMoved;
}