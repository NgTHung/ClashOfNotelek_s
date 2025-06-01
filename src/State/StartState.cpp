#include "State/StartState.hpp"
#include "Utility/Logger.hpp"

// Define start State

StartState::StartState(const sf::RenderWindow &Window) : m_Player(Window)
{
}

bool StartState::Render(sf::RenderTarget &Renderer)
{
    m_Player.Render(Renderer);
    return true;
}

bool StartState::HandleEvent()
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
        case GlobalEventType::PlayerAttacked:
        {
            this->m_Player.AddEvent(TopEvent.value());
            TopEvent.reset();
            continue;
        }
        default:
        {
            throw "Incorrect populated Event";
        }
        }
    }
    this->m_Player.HandleEvent();
    return true;
}

bool StartState::HandleInput(const std::optional<sf::Event> Event)
{
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        sf::Vector2f OldPos = this->m_Player.GetPosition();
        sf::Vector2f NewPos = OldPos;
        bool MovementRequired = false;
        constexpr float MoveAmount = 10.f;

        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::W:
        {
            NewPos.y -= MoveAmount;
            MovementRequired = true;
            break;
        }
        case sf::Keyboard::Scancode::A:
        {
            NewPos.x -= MoveAmount;
            MovementRequired = true;
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            NewPos.y += MoveAmount;
            MovementRequired = true;
            break;
        }
        case sf::Keyboard::Scancode::D:
        {
            NewPos.x += MoveAmount;
            MovementRequired = true;
            break;
        }
        default:
        {
            break;
        }
        }
        if (MovementRequired)
        {
            auto MoveCommand = std::make_unique<MovePlayerCommand>(this->m_Player, NewPos);
            MoveCommand->execute();
            // Share the Event
            this->m_EventQueue.PushEvent<PlayerMovedEvent>(this->m_Player, OldPos, NewPos);
            return true;
        }
    }
    return m_Player.HandleInput(Event);
}

bool StartState::FixLagUpdate(const sf::Time &DT)
{
    return m_Player.FixLagUpdate(DT);
}

bool StartState::Update(const sf::Time &DT)
{
    return m_Player.Update(DT);
}

// Define PlayerEvent

PlayerMovedEvent::PlayerMovedEvent(Player &Player, sf::Vector2f OldPos, sf::Vector2f NewPos) : m_NewPosition(NewPos), m_OldPosition(OldPos), m_Player(Player) {};

const GlobalEventType PlayerMovedEvent::GetEventType() const
{
    return GlobalEventType::PlayerMoved;
}

// Define PlayerCommand

void MovePlayerCommand::execute()
{
    this->m_Player.setPosition(this->m_NewPosition);
}

sf::Vector2f MovePlayerCommand::GetNewPosition() const
{
    return this->m_NewPosition;
}

MovePlayerCommand::MovePlayerCommand(Player &Player, const sf::Vector2f NewPos) : m_NewPosition(NewPos), m_Player(Player) {};
