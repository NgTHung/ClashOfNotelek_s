#pragma once
#include "State/ScreenState.hpp"
#include "Graphic/Player.hpp"
#include <SFML/Graphics.hpp>

class StartState : public ScreenState
{
public:
    StartState(const sf::RenderWindow &Window);
    ~StartState() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleEvent() override;
    bool HandleInput(std::optional<sf::Event> Event) override;
    bool FixLagUpdate(const sf::Time &DT) override;
    // Player function
private:
    Player m_Player;
};

class PlayerMovedEvent : public BaseEvent
{
private:
    const sf::Vector2f m_NewPosition;
    const sf::Vector2f m_OldPosition;
    Player &m_Player;

public:
    ~PlayerMovedEvent() = default;
    PlayerMovedEvent(Player &Player, sf::Vector2f OldPos, sf::Vector2f NewPos);
    const GlobalEventType GetEventType() const override;
};

class MovePlayerCommand : public BaseCommand
{
private:
    const sf::Vector2f m_NewPosition;
    Player &m_Player;

public:
    MovePlayerCommand(Player &Player, sf::Vector2f NewPos);
    sf::Vector2f GetNewPosition() const;
    void execute() override;
};