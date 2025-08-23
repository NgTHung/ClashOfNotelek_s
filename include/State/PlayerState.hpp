#pragma once
#include "BaseState.hpp"
#include "Command/PlayerCommand.hpp"
#include "Graphic/Player.hpp"
#include "Event/EventDispatcher.hpp"

class BaseCommand;
class Player;

class PlayerState : public BaseState<Player>
{
protected:
    std::shared_ptr<BaseCommand> m_WPressedCommand = nullptr;
    std::shared_ptr<BaseCommand> m_APressedCommand = nullptr;
    std::shared_ptr<BaseCommand> m_SPressedCommand = nullptr;
    std::shared_ptr<BaseCommand> m_DPressedCommand = nullptr;
    std::shared_ptr<BaseCommand> m_WReleaseCommand = nullptr;
    std::shared_ptr<BaseCommand> m_AReleaseCommand = nullptr;
    std::shared_ptr<BaseCommand> m_SReleaseCommand = nullptr;
    std::shared_ptr<BaseCommand> m_DReleaseCommand = nullptr;
    std::shared_ptr<BaseCommand> m_SpacePressedCommand = nullptr;

public:
    PlayerState(Player &PlayerInstance);
    void EnterState() override = 0;
    void ExitState() override = 0;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override = 0;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override = 0;
};

class StandingState : public PlayerState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    StandingState(Player &PlayerInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class MovingState : public PlayerState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    MovingState(Player &PlayerInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};