#include "State/SpriteState.hpp"
#include "Graphic/Player.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Graphic/Sprite.hpp"
#include "State/HomeScreen.hpp"
#include "Utility/Enviroment.hpp"

CharacterState::CharacterState(Engine &g_Engine, Character &CharacterInstance) : BaseState(CharacterInstance),
    m_Engine(g_Engine) {
    m_LeftClickCommand = std::make_shared<CharacterAttackCommand>(CharacterInstance);
}

std::unique_ptr<BaseState<Character> > CharacterState::HandleInput(std::optional<sf::Event> Event) {
    std::shared_ptr<BaseCommand> currentCommand = nullptr;
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>()) {
        switch (KeyPressed->scancode) {
            // case sf::Keyboard::Scancode::Space:
            // {
            //     currentCommand = this->m_SpacePressedCommand;
            //     break;
            // }
            case sf::Keyboard::Scancode::W: {
                currentCommand = this->m_WPressedCommand;
                break;
            }
            case sf::Keyboard::Scancode::A: {
                currentCommand = this->m_APressedCommand;
                break;
            }
            case sf::Keyboard::Scancode::S: {
                currentCommand = this->m_SPressedCommand;
                break;
            }
            case sf::Keyboard::Scancode::D: {
                currentCommand = this->m_DPressedCommand;
                break;
            }
            default: {
                break;
            }
        }
    }
    if (const auto *KeyPressed = Event->getIf<sf::Event::MouseButtonPressed>()) {
        if (KeyPressed->button == sf::Mouse::Button::Left)
            currentCommand = this->m_LeftClickCommand;
    }
    if (const auto *KeyReleased = Event->getIf<sf::Event::KeyReleased>()) {
        switch (KeyReleased->scancode) {
            case sf::Keyboard::Scancode::W: {
                currentCommand = this->m_WReleaseCommand;
                break;
            }
            case sf::Keyboard::Scancode::A: {
                currentCommand = this->m_AReleaseCommand;
                break;
            }
            case sf::Keyboard::Scancode::S: {
                currentCommand = this->m_SReleaseCommand;
                break;
            }
            case sf::Keyboard::Scancode::D: {
                currentCommand = this->m_DReleaseCommand;
                break;
            }
            default: {
                break;
            }
        }
    }
    if (currentCommand.get() != nullptr) {
        currentCommand->execute();
    }
    return nullptr;
}

CharacterStandingState::CharacterStandingState(Engine &g_Engine, Character &CharacterInstance) : CharacterState(
    g_Engine, CharacterInstance) {
    m_WPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::EAST);
    // m_SpacePressedCommand = std::make_shared<AdvancePlayerIndexCommand>(CharacterInstance);
}

void CharacterStandingState::EnterState() {
    this->m_Instance.ResetIndex();
    this->m_Instance.UpdateAnimationTagIDLE();
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event) { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::CharacterMoved, m_Listener);
}

void CharacterStandingState::ExitState() {
}

std::unique_ptr<BaseState<Character> > CharacterStandingState::HandleInput(std::optional<sf::Event> Event) {
    return CharacterState::HandleInput(Event);
}

std::unique_ptr<BaseState<Character> > CharacterStandingState::FixLagUpdate(const sf::Time &DT) {
    return nullptr;
}

std::unique_ptr<BaseState<Character> > CharacterStandingState::Update(const sf::Time &DT) {
    this->m_Instance.NextFrame(Enviroment::CharacterStandingFrameCount);
    return nullptr;
}

bool CharacterStandingState::HandleEvent(const std::shared_ptr<BaseEvent> Event) {
    if (!Event) {
        LOG_ERROR("Received null event in CharacterStandingState");
        return false;
    }

    switch (Event->GetEventType()) {
        case GlobalEventType::CharacterMoved: {
            this->m_Instance.ChangeState(std::make_unique<CharacterMovingState>(m_Engine, this->m_Instance));
            return true;
        }
        case GlobalEventType::CharacterAttack: {
            if (this->m_Instance.GetWeapon().IsAttacking()) {
                this->m_Instance.ChangeState(std::make_unique<CharacterAttackState>(m_Engine, this->m_Instance));
                return true;
            }
            return false;
        }
        default: {
            LOG_ERROR("Unhandled event type in CharacterStandingState: {}", static_cast<int>(Event->GetEventType()));
            return false;
        }
    }
}

CharacterMovingState::CharacterMovingState(Engine &g_Engine, Character &CharacterInstance) : CharacterState(
    g_Engine, CharacterInstance) {
    m_WPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::NORTH);
    m_APressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::WEST);
    m_SPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::SOUTH);
    m_DPressedCommand = std::make_shared<MoveCharacterCommand>(CharacterInstance, Direction::EAST);
    m_WReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::NORTH);
    m_AReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::WEST);
    m_SReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::SOUTH);
    m_DReleaseCommand = std::make_shared<StopCharacterMovingCommand>(CharacterInstance, Direction::EAST);
}

void CharacterMovingState::EnterState() {
    this->m_Instance.ResetIndex();
    this->m_Instance.UpdateAnimationTagWALK();
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event) { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::CharacterStopMoved, this->m_Listener);
}

void CharacterMovingState::ExitState() {
    EventDispatcher::GetInstance().UnRegisterListener(GlobalEventType::CharacterStopMoved, this->m_Listener);
}

std::unique_ptr<BaseState<Character> > CharacterMovingState::HandleInput(std::optional<sf::Event> Event) {
    return CharacterState::HandleInput(Event);
}

std::unique_ptr<BaseState<Character> > CharacterMovingState::FixLagUpdate(const sf::Time &DT) {
    return nullptr;
}

std::unique_ptr<BaseState<Character> > CharacterMovingState::Update(const sf::Time &DT) {
    this->m_Instance.UpdateAnimationTagWALK();
    sf::Vector2f NewPosition = sf::Vector2f(Enviroment::BaseLocation);
    for (const auto it: this->m_Instance.GetDirection()) {
        switch (it) {
            case Direction::NONE: {
                LOG_DEBUG("ERROR in handle input");
                break;
            }
            case Direction::WEST: {
                NewPosition.x -= Enviroment::Velocity;
                break;
            }
            case Direction::EAST: {
                NewPosition.x += Enviroment::Velocity;
                break;
            }
            case Direction::NORTH: {
                NewPosition.y -= Enviroment::Velocity;
                break;
            }
            case Direction::SOUTH: {
                NewPosition.y += Enviroment::Velocity;
            }
        }
        this->m_Instance.SetDirection(it);
    }

    NewPosition *= DT.asSeconds();

    if (this->m_Instance.GetDirection().size() == 2) {
        NewPosition *= Enviroment::VelocityNormalizationValue;
    }
    if (m_Engine.GetCollisionSystem().IsFree(this->m_Instance.GetPosition() + NewPosition, m_Instance, Enviroment::PlayerCollisionLayer)) {
        this->m_Instance.SetPosition(NewPosition + this->m_Instance.GetPosition());
    } else {
        LOG_DEBUG("Character Moving State: Collision Detected, not moving");
    }
    this->m_Instance.NextFrame(Enviroment::CharacterMovingFrameCount);
    return nullptr;
}

bool CharacterMovingState::HandleEvent(const std::shared_ptr<BaseEvent> Event) {
    if (!Event) {
        LOG_ERROR("Received null event in CharacterStandingState");
        return false;
    }

    switch (Event->GetEventType()) {
        case GlobalEventType::CharacterStopMoved: {
            if (this->m_Instance.GetDirection().empty()) {
                this->m_Instance.ChangeState(std::make_unique<CharacterStandingState>(m_Engine, this->m_Instance));
                return true;
            }
            return false;
        }
        case GlobalEventType::CharacterAttack: {
            if (this->m_Instance.GetWeapon().IsAttacking()) {
                this->m_Instance.ChangeState(std::make_unique<CharacterAttackState>(m_Engine, this->m_Instance));
                return true;
            }
            return false;
        }
        default: {
            LOG_ERROR("Unhandled event type in CharacterStandingState: {}", static_cast<int>(Event->GetEventType()));
            return false;
        }
    }
}

CharacterAttackState::CharacterAttackState(Engine &g_Engine, Character &CharacterInstance): CharacterState(
    g_Engine, CharacterInstance) {
}

void CharacterAttackState::EnterState() {
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event) { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
        GlobalEventType::CharacterAttack, this->m_Listener);
}

void CharacterAttackState::ExitState() {
    return;
}

bool CharacterAttackState::HandleEvent(std::shared_ptr<BaseEvent> Event) {
    if (!Event) {
        LOG_ERROR("Received null event in CharacterAttackState");
        return false;
    }
    switch (Event->GetEventType()) {
        case GlobalEventType::CharacterStopMoved: {
            if (this->m_Instance.GetDirection().empty()) {
                this->m_Instance.ChangeState(std::make_unique<CharacterStandingState>(m_Engine, this->m_Instance));
                return true;
            }
            return false;
        }
        case GlobalEventType::CharacterMoved: {
            this->m_Instance.ChangeState(std::make_unique<CharacterMovingState>(m_Engine, this->m_Instance));
            return true;
        }
        default: {
            LOG_ERROR("Unhandled event type in CharacterStandingState: {}", static_cast<int>(Event->GetEventType()));
            return false;
        }
    }
}

std::unique_ptr<BaseState<Character> > CharacterAttackState::HandleInput(std::optional<sf::Event> Event) {
    return CharacterState::HandleInput(Event);
}

std::unique_ptr<BaseState<Character> > CharacterAttackState::FixLagUpdate(const sf::Time &DT) {
    return nullptr;
}

std::unique_ptr<BaseState<Character> > CharacterAttackState::Update(const sf::Time &DT) {
    return nullptr;
}
