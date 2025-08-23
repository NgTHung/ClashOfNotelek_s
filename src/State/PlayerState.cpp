#include "State/PlayerState.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Graphic/Player.hpp"
#include "State/StartScreen.hpp"
#include "Utility/Environment.hpp"

PlayerState::PlayerState(Player &PlayerInstance) : BaseState(PlayerInstance)
{
}

std::unique_ptr<BaseState<Player>> PlayerState::HandleInput(std::optional<sf::Event> Event)
{
    std::shared_ptr<BaseCommand> currentCommand = nullptr;
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::Space:
        {
            currentCommand = this->m_SpacePressedCommand;
            break;
        }
        case sf::Keyboard::Scancode::W:
        {
            currentCommand = this->m_WPressedCommand;
            break;
        }
        case sf::Keyboard::Scancode::A:
        {
            currentCommand = this->m_APressedCommand;
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            currentCommand = this->m_SPressedCommand;
            break;
        }
        case sf::Keyboard::Scancode::D:
        {
            currentCommand = this->m_DPressedCommand;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    if (const auto *KeyReleased = Event->getIf<sf::Event::KeyReleased>())
    {
        switch (KeyReleased->scancode)
        {
        case sf::Keyboard::Scancode::W:
        {
            currentCommand = this->m_WReleaseCommand;
            break;
        }
        case sf::Keyboard::Scancode::A:
        {
            currentCommand = this->m_AReleaseCommand;
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            currentCommand = this->m_SReleaseCommand;
            break;
        }
        case sf::Keyboard::Scancode::D:
        {
            currentCommand = this->m_DReleaseCommand;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    if (currentCommand != nullptr)
    {
        currentCommand->execute();
    }
    return nullptr;
}

StandingState::StandingState(Player &PlayerInstance) : PlayerState(PlayerInstance)
{
    m_WPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::EAST);
    m_SpacePressedCommand = std::make_shared<AdvancePlayerIndexCommand>(PlayerInstance);
}

void StandingState::EnterState()
{
    this->m_Instance.ResetIndex();
    this->m_Instance.SetName("Hello World");
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event)
    { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::PlayerMoved, m_Listener);
}

void StandingState::ExitState()
{
}
std::unique_ptr<BaseState<Player>> StandingState::Update(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Player>> StandingState::HandleInput(const std::optional<sf::Event> Event)
{
    return PlayerState::HandleInput(Event);
}

bool StandingState::HandleEvent(const std::shared_ptr<BaseEvent> &Event)
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
    m_WPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MovePlayerCommand>(PlayerInstance, Direction::EAST);
    m_WReleaseCommand = std::make_shared<StopPlayerMovingCommand>(PlayerInstance, Direction::NORTH);
    m_AReleaseCommand = std::make_shared<StopPlayerMovingCommand>(PlayerInstance, Direction::WEST);
    m_SReleaseCommand = std::make_shared<StopPlayerMovingCommand>(PlayerInstance, Direction::SOUTH);
    m_DReleaseCommand = std::make_shared<StopPlayerMovingCommand>(PlayerInstance, Direction::EAST);
}

void MovingState::EnterState()
{
    this->m_Instance.SetName("Goodbye World");
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event)
    { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::PlayerStopMoved, this->m_Listener);
}

void MovingState::ExitState()
{
    EventDispatcher::GetInstance().UnRegisterListener(GlobalEventType::PlayerStopMoved, this->m_Listener);
}

std::unique_ptr<BaseState<Player>> MovingState::HandleInput(const std::optional<sf::Event> Event)
{
    return PlayerState::HandleInput(Event);
}

std::unique_ptr<BaseState<Player>> MovingState::Update(const sf::Time &DT)
{
    auto NewPosition = sf::Vector2f(Environment::BaseLocation);
    for (const auto it : this->m_Instance.GetDirection())
    {
        switch (it)
        {
        case Direction::NONE:
        {
            LOG_DEBUG("ERROR in handle input");
            break;
        }
        case Direction::WEST:
        {
            NewPosition.x -= Environment::Velocity;
            break;
        }
        case Direction::EAST:
        {
            NewPosition.x += Environment::Velocity;
            break;
        }
        case Direction::NORTH:
        {
            NewPosition.y -= Environment::Velocity;
            break;
        }
        case Direction::SOUTH:
        {
            NewPosition.y += Environment::Velocity;
        }
        }
    }
    if (this->m_Instance.GetDirection().size() == 2)
    {
        NewPosition *= Environment::VelocityNormalizationValue;
    }
    this->m_Instance.setPosition(NewPosition + this->m_Instance.GetPosition());
    return nullptr;
}

bool MovingState::HandleEvent(const std::shared_ptr<BaseEvent> &Event)
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
        if (this->m_Instance.GetDirection().empty())
        {
            this->m_Instance.ChangeState(std::make_unique<StandingState>(this->m_Instance));
            return true;
        }
        return false;
    }
    default:
    {
        LOG_ERROR("Unhandled event type in StandingState: {}", static_cast<int>(Event->GetEventType()));
        return false;
    }
    }
}