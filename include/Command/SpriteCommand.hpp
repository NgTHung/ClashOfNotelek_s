#pragma once

#include "Command/Command.hpp"
#include "Graphic/Sprite.hpp"

enum class Direction;
class Character;

class MoveCharacterCommand : public BaseCommand {
private:
    Character &m_Character;
    Direction m_NewDirection;
public:
    MoveCharacterCommand(Character& g_Character, const Direction &NewDirection);
    void execute() override;
};

class StopCharacterMovingCommand : public BaseCommand {
private:
    Character &m_Character;
    Direction m_OldDirection;
public:
    StopCharacterMovingCommand(Character& g_Character, const Direction &OldDirection);
    void execute() override;
};

