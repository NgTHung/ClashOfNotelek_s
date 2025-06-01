#pragma once
#include "State/ScreenState.hpp"

class Player;

class PlayerState
{
public:
    virtual ~PlayerState() = default;
    virtual void EnterState(Player &PlayerInstance) = 0;
    virtual void ExitState(Player &PlayerInstance) = 0;
    virtual std::unique_ptr<PlayerState> FixLagUpdate(Player &PlayerInstance, const sf::Time &DT) = 0;
    virtual std::unique_ptr<PlayerState> HandleEvent(Player &PlayerInstance) = 0;
    virtual std::unique_ptr<PlayerState> HandleInput(Player &PlayerInstance, const std::optional<sf::Event> Event) = 0;
    virtual std::unique_ptr<PlayerState> Update(Player &PlayerInstance, const sf::Time &DT) = 0;
    virtual void AddEvent(std::shared_ptr<BaseEvent> Event) = 0;

protected:
    EventQueue m_EventQueue;
};

class StandingState : public PlayerState
{
public:
    StandingState() = default;
    void EnterState(Player &PlayerInstance) override;
    void ExitState(Player &PlayerInstance) override;
    std::unique_ptr<PlayerState> FixLagUpdate(Player &PlayerInstance, const sf::Time &DT) override;
    std::unique_ptr<PlayerState> HandleEvent(Player &PlayerInstance) override;
    std::unique_ptr<PlayerState> HandleInput(Player &PlayerInstance, const std::optional<sf::Event> Event) override;
    std::unique_ptr<PlayerState> Update(Player &PlayerInstance, const sf::Time &DT) override;
    void AddEvent(std::shared_ptr<BaseEvent> Event) override;
};

class MovingState : public PlayerState
{
public:
    MovingState() = default;
    void EnterState(Player &PlayerInstance) override;
    void ExitState(Player &PlayerInstance) override;
    std::unique_ptr<PlayerState> FixLagUpdate(Player &PlayerInstance, const sf::Time &DT) override;
    std::unique_ptr<PlayerState> HandleEvent(Player &PlayerInstance) override;
    std::unique_ptr<PlayerState> HandleInput(Player &PlayerInstance, const std::optional<sf::Event> Event) override;
    std::unique_ptr<PlayerState> Update(Player &PlayerInstance, const sf::Time &DT) override;
    void AddEvent(std::shared_ptr<BaseEvent> Event) override;
};