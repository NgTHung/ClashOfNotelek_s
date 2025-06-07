#pragma once
#include "BaseState.hpp"
#include "Command/SpriteCommand.hpp"
#include "Graphic/Sprite.hpp"
#include "State/Screen.hpp"
#include "Event/EventDispatcher.hpp"

class BaseCommand;  
class Character;

class CharacterState : public BaseState<Character>
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
    CharacterState(Character &CharacterInstance);
    void EnterState() override = 0;
    void ExitState() override = 0;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class CharacterStandingState : public CharacterState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    CharacterStandingState(Character &CharacterInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class CharacterMovingState: public CharacterState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    CharacterMovingState(Character &CharacterInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(std::shared_ptr<BaseEvent>) override;
    std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};