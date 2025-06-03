#pragma once

#include "Command/Command.hpp"

enum class Direction;
class Player;

class MovePlayerCommand : public BaseCommand {
private:
    Player &m_Player;
    Direction m_NewDirection;
public:
    MovePlayerCommand(Player& g_Player, const Direction &NewDirection);
    void execute() override;
};

class StopPlayerMovingCommand : public BaseCommand {
private:
    Player &m_Player;
    Direction m_OldDirection;
public:
    StopPlayerMovingCommand(Player& g_Player, const Direction &OldDirection);
    void execute() override;
};

class AdvancePlayerIndexCommand : public BaseCommand {
private:
    Player &m_Player;
public:
    AdvancePlayerIndexCommand(Player &g_Player);
    void execute() override;
};