#pragma once
#include "Event.hpp"

enum class Direction;
class Player;

class PlayerMovedEvent: public BaseEvent {
private:
    Direction m_NewDirection;
    Player &m_Player;
public:
    const GlobalEventType GetEventType() const override;
    PlayerMovedEvent(Player &Player, const Direction &NewDirection);
};

class PlayerStopMoved: public BaseEvent {
private:
    Direction m_OldDirection;
    Player &m_Player;
public:
    const GlobalEventType GetEventType() const override;
    PlayerStopMoved(Player &Player, const Direction &OldDirection);
};