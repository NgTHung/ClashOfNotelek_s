#pragma once
#include "BaseState.hpp"
#include "Graphic/Sprite.hpp"
#include "Event/EventDispatcher.hpp"

class BaseCommand;  
class Character;
class Engine;

class CharacterState : public BaseState<Character>
{
protected:
    Engine &m_Engine;
    std::shared_ptr<BaseCommand> m_LeftClickCommand = nullptr;
    std::shared_ptr<BaseCommand> m_LeftClickReleaseCommand = nullptr;
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
    CharacterState(Engine &g_Engine, Character &CharacterInstance);
    void EnterState() override = 0;
    void ExitState() override = 0;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override = 0;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override = 0;
};

class CharacterStandingState : public CharacterState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    CharacterStandingState(Engine &g_Engine, Character &CharacterInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class CharacterMovingState: public CharacterState
{
private:
    EventDispatcher::EventListener m_Listener;

public:
    CharacterMovingState(Engine &g_Engine, Character &CharacterInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

class CharacterAttackState: public CharacterState{
private:
    EventDispatcher::EventListener m_Listener;

public:
    CharacterAttackState(Engine &g_Engine, Character &CharacterInstance);
    void EnterState() override;
    void ExitState() override;
    bool HandleEvent(const std::shared_ptr<BaseEvent>&) override;
    std::unique_ptr<BaseState> HandleInput(std::optional<sf::Event> Event) override;
    std::unique_ptr<BaseState> Update(const sf::Time &DT) override;
};

