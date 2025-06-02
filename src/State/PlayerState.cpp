#include "State/PlayerState.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Graphic/Player.hpp"
#include "State/StartScreen.hpp"

PlayerState::PlayerState(Player &PlayerInstance) : BaseState(PlayerInstance)
{
}

StandingState::StandingState(Player &PlayerInstance) : PlayerState(PlayerInstance)
{
}

void StandingState::EnterState()
{
    this->m_Instance.ResetIndex();
    this->m_Instance.SetName("Hello World");
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::PlayerMoved,
        [this](const std::shared_ptr<BaseEvent> &Event)
        { return this->HandleEvent(Event); });
}

void StandingState::ExitState()
{
}

std::unique_ptr<BaseState<Player>> StandingState::FixLagUpdate(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Player>> StandingState::Update(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Player>> StandingState::HandleInput(const std::optional<sf::Event> Event)
{
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::Space:
        {
            this->m_Instance.AdvanceIndex();
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

bool StandingState::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    if (!Event)
    {
        LOG_ERROR("Received null event in StandingState");
        return false;
    }

    switch (Event->GetEventType())
    {
    case GlobalEventType::PlayerMoved:
    {
        this->m_Instance.ChangeState(std::make_unique<MovingState>(this->m_Instance));
        return true;
    }
    default:
    {
        LOG_ERROR("Unhandled event type in StandingState: {}", static_cast<int>(Event->GetEventType()));
        return false;
    }
    }
}

MovingState::MovingState(Player &PlayerInstance) : PlayerState(PlayerInstance)
{
}

void MovingState::EnterState()
{
    this->m_Instance.SetName("Goodbye World");
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::PlayerStopMoved,
        [this](const std::shared_ptr<BaseEvent> &Event)
        { return this->HandleEvent(Event); });
}

void MovingState::ExitState()
{
}

std::unique_ptr<BaseState<Player>> MovingState::HandleInput(const std::optional<sf::Event> Event)
{
    if (const auto *KeyReleased = Event->getIf<sf::Event::KeyReleased>())
    {
        switch (KeyReleased->scancode)
        {
        case sf::Keyboard::Scancode::W:
        case sf::Keyboard::Scancode::A:
        case sf::Keyboard::Scancode::S:
        case sf::Keyboard::Scancode::D:
        {
            return std::make_unique<StandingState>(m_Instance);
        }
        default:
        {
            break;
        }
        }
    }
    return nullptr;
}

std::unique_ptr<BaseState<Player>> MovingState::FixLagUpdate(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Player>> MovingState::Update(const sf::Time &DT)
{
    return nullptr;
}

bool MovingState::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    if (!Event)
    {
        LOG_ERROR("Received null event in StandingState");
        return false;
    }

    switch (Event->GetEventType())
    {
    case GlobalEventType::PlayerStopMoved:
    {
        this->m_Instance.ChangeState(std::make_unique<StandingState>(this->m_Instance));
        return true;
    }
    default:
    {
        LOG_ERROR("Unhandled event type in StandingState: {}", static_cast<int>(Event->GetEventType()));
        return false;
    }
    }
}