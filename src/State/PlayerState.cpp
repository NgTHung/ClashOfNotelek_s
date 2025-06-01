#include "State/PlayerState.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Graphic/Player.hpp"

void StandingState::EnterState(Player &PlayerInstance)
{
    PlayerInstance.ResetIndex();
    PlayerInstance.SetName("Hello World");
}

void StandingState::ExitState(Player &PlayerInstance)
{
}

void StandingState::AddEvent(std::shared_ptr<BaseEvent> Event)
{
    this->m_EventQueue.PushEvent(Event);
}

std::unique_ptr<PlayerState> StandingState::FixLagUpdate(Player &PlayerInstance, const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<PlayerState> StandingState::Update(Player &PlayerInstance, const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<PlayerState> StandingState::HandleEvent(Player &PlayerInstance)
{
    while (!m_EventQueue.IsEmpty())
    {
        auto TopEvent = m_EventQueue.PopEvent();
        if (!TopEvent.has_value())
            continue;
        LOG_DEBUG("Ref count: {}", TopEvent->use_count());
        switch (TopEvent->get()->GetEventType())
        {
        case GlobalEventType::Generic:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::PlayerAttacked:
        case GlobalEventType::GameQuit:
        {
            TopEvent.reset();
            continue;
        }
        case GlobalEventType::PlayerAction:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::PlayerMoved:
        {
            TopEvent.reset();
            return std::make_unique<MovingState>();
        }
        default:
        {
            throw "Incorrect populated Event";
        }
        }
    }
    return nullptr;
}

std::unique_ptr<PlayerState> StandingState::HandleInput(Player &PlayerInstance, const std::optional<sf::Event> Event)
{
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::Space:
        {
            PlayerInstance.AdvanceIndex();
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return nullptr;
}

void MovingState::EnterState(Player &PlayerInstance)
{
    PlayerInstance.SetName("Goodbye World");
}

void MovingState::ExitState(Player &PlayerInstance)
{
}

void MovingState::AddEvent(std::shared_ptr<BaseEvent> Event)
{
    this->m_EventQueue.PushEvent(Event);
}

std::unique_ptr<PlayerState> MovingState::HandleInput(Player &PlayerInstance, const std::optional<sf::Event> Event)
{
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyReleased>())
    {
        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::W:
        case sf::Keyboard::Scancode::A:
        case sf::Keyboard::Scancode::S:
        case sf::Keyboard::Scancode::D:
        {
            return std::make_unique<StandingState>();
        }
        default:
        {
            break;
        }
        }
    }
    return nullptr;
}

std::unique_ptr<PlayerState> MovingState::HandleEvent(Player &PlayerInstance)
{
    while (!m_EventQueue.IsEmpty())
    {
        auto TopEvent = m_EventQueue.PopEvent();
        if (!TopEvent.has_value())
            continue;
        switch (TopEvent->get()->GetEventType())
        {
        case GlobalEventType::Generic:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::PlayerAttacked:
        case GlobalEventType::GameQuit:
        case GlobalEventType::PlayerMoved:
        {
            TopEvent.reset();
            continue;
        }
        case GlobalEventType::PlayerAction:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        default:
        {
            throw "Incorrect populated Event";
        }
        }
    }
    return nullptr;
}

std::unique_ptr<PlayerState> MovingState::FixLagUpdate(Player &PlayerInstance, const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<PlayerState> MovingState::Update(Player &PlayerInstance, const sf::Time &DT)
{
    return nullptr;
}
