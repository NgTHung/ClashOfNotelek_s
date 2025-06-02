#pragma once
#include "BaseState.hpp"
#include "Graphic/Player.hpp"
#include "State/Screen.hpp"

class Player;

class PlayerState : public BaseState<Player>
{
public:
    PlayerState(Player& PlayerInstance);
    void EnterState() override = 0;
    void ExitState() override = 0;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override = 0;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override = 0;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override = 0;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override = 0;

};

class StandingState : public PlayerState
{
public:
    StandingState(Player& PlayerInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class MovingState : public PlayerState
{
public:
    MovingState(Player& PlayerInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};