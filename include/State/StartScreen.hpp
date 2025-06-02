#pragma once
#include "State/Screen.hpp"
#include "Graphic/Player.hpp"
#include "Command/Command.hpp"
#include <SFML/Graphics.hpp>

class StartScreen : public Screen
{
public:
    StartScreen(Engine &g_Engine);
    ~StartScreen() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleInput(std::optional<sf::Event> Event) override;
    bool FixLagUpdate(const sf::Time &DT) override;
    bool HandleEvent(std::shared_ptr<BaseEvent> Event) override;
    // Player function
private:
    Player m_Player;
};

class PlayerMovedEvent : public BaseEvent
{
private:
    const Direction m_NewDirection;
    Player &m_Player;

public:
    ~PlayerMovedEvent() = default;
    PlayerMovedEvent(Player &Player, const Direction &NewDirection);
    const GlobalEventType GetEventType() const override;
};
class PlayerStopMoved : public BaseEvent
{
private:
    Player &m_Player;

public:
    ~PlayerStopMoved() = default;
    PlayerStopMoved(Player &Player);
    const GlobalEventType GetEventType() const override;
};

class MovePlayerCommand : public BaseCommand
{
private:
    Direction m_NewDirection;
    Player &m_Player;

public:
    MovePlayerCommand(Player &Player, const Direction NewDirection);
    Direction GetNewDirection() const;
    void execute() override;
};

class ReverseAdd : public BaseCommand
{
private:
    Direction m_NewDirection;
    Player &m_Player;

public:
    ReverseAdd(Player &Player, const Direction NewDirection);
    Direction GetNewDirection() const;
    void execute() override;
};