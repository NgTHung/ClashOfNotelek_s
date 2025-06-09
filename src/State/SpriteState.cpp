#include "State/SpriteState.hpp"
#include "Graphic/Player.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Graphic/Sprite.hpp"
#include "State/HomeScreen.hpp"
#include <cmath>

CharacterState::CharacterState(Character &CharacterInstance) : BaseState(CharacterInstance)
{
}

std::unique_ptr<BaseState<Character>> CharacterState::HandleInput(std::optional<sf::Event> Event)
{
    std::shared_ptr<BaseCommand> currentCommand = nullptr;
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        switch (KeyPressed->scancode)
        {
        // case sf::Keyboard::Scancode::Space:
        // {
        //     currentCommand = this->m_SpacePressedCommand;
        //     break;
        // }
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
    if (currentCommand.get() != nullptr)
    {
        currentCommand->execute();
    }
    return nullptr;
}

CharacterStandingState::CharacterStandingState(Character &CharacterInstance) : CharacterState(CharacterInstance)
{
    m_WPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::EAST);
    // m_SpacePressedCommand = std::make_shared<AdvancePlayerIndexCommand>(CharacterInstance);
}

void CharacterStandingState::EnterState()
{
    this->m_Instance.ResetIndex();
    this->m_Instance.UpdateAnimationTagIDLE();
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event)
    { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::CharacterMoved, m_Listener);
}

void CharacterStandingState::ExitState()
{
}

std::unique_ptr<BaseState<Character>> CharacterStandingState::HandleInput(std::optional<sf::Event> Event)
{
    return CharacterState::HandleInput(Event);
}

std::unique_ptr<BaseState<Character>> CharacterStandingState::FixLagUpdate(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Character>> CharacterStandingState::Update(const sf::Time &DT)
{
    this->m_Instance.NextFrame(5);
    return nullptr;
}

bool CharacterStandingState::HandleEvent(const std::shared_ptr<BaseEvent> Event)
{
    if (!Event)
    {
        LOG_ERROR("Received null event in CharacterStandingState");
        return false;
    }

    switch (Event->GetEventType())
    {
    case GlobalEventType::CharacterMoved:
    {
        this->m_Instance.ChangeState(std::make_unique<CharacterMovingState>(this->m_Instance));
        return true;
    }
    default:
    {
        LOG_ERROR("Unhandled event type in CharacterStandingState: {}", static_cast<int>(Event->GetEventType()));
        return false;
    }
    }
}

CharacterMovingState::CharacterMovingState(Character &CharacterInstance) : CharacterState(CharacterInstance)
{
    m_WPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::EAST);
    m_WReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::NORTH);
    m_AReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::WEST);
    m_SReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::SOUTH);
    m_DReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::EAST);
}

void CharacterMovingState::EnterState()
{
    this->m_Instance.ResetIndex();
    this->m_Instance.UpdateAnimationTagWALK();
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event)
    { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::CharacterStopMoved, this->m_Listener);
}

void CharacterMovingState::ExitState()
{
    EventDispatcher::GetInstance().UnRegisterListener(GlobalEventType::CharacterStopMoved, this->m_Listener);
}

std::unique_ptr<BaseState<Character>> CharacterMovingState::HandleInput(std::optional<sf::Event> Event)
{
    return CharacterState::HandleInput(Event);
}

std::unique_ptr<BaseState<Character>> CharacterMovingState::FixLagUpdate(const sf::Time &DT)
{
    return nullptr;
}

std::unique_ptr<BaseState<Character>> CharacterMovingState::Update(const sf::Time &DT)
{
    this->m_Instance.UpdateAnimationTagWALK();
    sf::Vector2f NewPosition = {0, 0};
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
            NewPosition.x -= 10;
            break;
        }
        case Direction::EAST:
        {
            NewPosition.x += 10;
            break;
        }
        case Direction::NORTH:
        {
            NewPosition.y -= 10;
            break;
        }
        case Direction::SOUTH:
        {
            NewPosition.y += 10;
        }
        }
        this->m_Instance.SetDirection(it);
    }
        
    if (this->m_Instance.GetDirection().size() == 2)
    {
        NewPosition.x *= (std::sqrt(2) / 2.f);
        NewPosition.y *= (std::sqrt(2) / 2.f);
    }
    this->m_Instance.SetPosition(NewPosition + this->m_Instance.GetPosition());
    this->m_Instance.NextFrame(7);
    return nullptr;
}

bool CharacterMovingState::HandleEvent(const std::shared_ptr<BaseEvent> Event)
{
    if (!Event)
    {
        LOG_ERROR("Received null event in CharacterStandingState");
        return false;
    }

    switch (Event->GetEventType())
    {
    case GlobalEventType::CharacterStopMoved:
    {
        if (this->m_Instance.GetDirection().empty())
        {
            this->m_Instance.ChangeState(std::make_unique<CharacterStandingState>(this->m_Instance));
            return true;
        }
        return false;
    }
    default:
    {
        LOG_ERROR("Unhandled event type in CharacterStandingState: {}", static_cast<int>(Event->GetEventType()));
        return false;
    }
    }
}