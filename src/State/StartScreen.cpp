#include "State/StartScreen.hpp"
#include "Utility/Logger.hpp"
// Define start State

StartScreen::StartScreen(Engine &g_Engine) : Screen(g_Engine), m_Player(g_Engine)
{
}

bool StartScreen::Render(sf::RenderTarget &Renderer)
{
    m_Player.Render(Renderer);
    return true;
}

bool StartScreen::HandleInput(const std::optional<sf::Event> Event)
{
    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        // sf::Vector2f OldPos = this->m_Player.GetPosition();
        // sf::Vector2f NewPos = OldPos;
        // bool MovementRequired = false;
        // constexpr float MoveAmount = 10.f;
        Direction currentDirection = Direction::NONE;
        switch (KeyPressed->scancode)
        {
        case sf::Keyboard::Scancode::W:
        {
            currentDirection = Direction::NORTH;
            break;
        }
        case sf::Keyboard::Scancode::A:
        {
            currentDirection = Direction::WEST;
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            currentDirection = Direction::SOUTH;
            break;
        }
        case sf::Keyboard::Scancode::D:
        {
            currentDirection = Direction::EAST;
            break;
        }
        default:
        {
            break;
        }
        }
        if (currentDirection != Direction::NONE)
        {
            auto MoveCommand = std::make_unique<MovePlayerCommand>(this->m_Player, currentDirection);
            MoveCommand->execute();
            // Share the Event
            this->m_Engine.PostEvent<PlayerMovedEvent>(this->m_Player, currentDirection);
            return true;
        }
    }
    if (const auto *KeyRelease = Event->getIf<sf::Event::KeyReleased>())
    {
        // sf::Vector2f OldPos = this->m_Player.GetPosition();
        // sf::Vector2f NewPos = OldPos;
        // bool MovementRequired = false;
        // constexpr float MoveAmount = 10.f;
        Direction currentDirection = Direction::NONE;
        BaseCommand *currentCommand = nullptr;
        switch (KeyRelease->scancode)
        {
        case sf::Keyboard::Scancode::W:
        {
            currentDirection = Direction::NORTH;
            break;
        }
        case sf::Keyboard::Scancode::A:
        {
            currentDirection = Direction::WEST;
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            currentDirection = Direction::SOUTH;
            break;
        }
        case sf::Keyboard::Scancode::D:
        {
            currentDirection = Direction::EAST;
            break;
        }
        default:
        {
            break;
        }
        }
        if (currentDirection != Direction::NONE)
        {
            auto MoveCommand = std::make_unique<ReverseAdd>(this->m_Player, currentDirection);
            MoveCommand->execute();
            // Share the Event
            this->m_Engine.PostEvent<PlayerStopMoved>(this->m_Player);
            return true;
        }
    }
    return m_Player.HandleInput(Event);
}

bool StartScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool StartScreen::FixLagUpdate(const sf::Time &DT)
{
    return m_Player.FixLagUpdate(DT);
}

bool StartScreen::Update(const sf::Time &DT)
{
    return m_Player.Update(DT);
}

// Define PlayerEvent

PlayerMovedEvent::PlayerMovedEvent(Player &Player, const Direction &NewDirection) : m_NewDirection(NewDirection), m_Player(Player) {};

const GlobalEventType PlayerMovedEvent::GetEventType() const
{
    return GlobalEventType::PlayerMoved;
}

// Define PlayerCommand

void MovePlayerCommand::execute()
{
    this->m_Player.AddDirection(this->m_NewDirection);
}

Direction MovePlayerCommand::GetNewDirection() const
{
    return this->m_NewDirection;
}

MovePlayerCommand::MovePlayerCommand(Player &Player, const Direction NewDirection) : m_NewDirection(NewDirection), m_Player(Player) {};

void ReverseAdd::execute()
{
    this->m_Player.RemoveDirection(this->m_NewDirection);
}

Direction ReverseAdd::GetNewDirection() const
{
    return this->m_NewDirection;
}

ReverseAdd::ReverseAdd(Player &Player, const Direction NewDirection) : m_NewDirection(NewDirection), m_Player(Player) {};

PlayerStopMoved::PlayerStopMoved(Player &Player) : m_Player(Player) {};
const GlobalEventType PlayerStopMoved::GetEventType() const
{
    return GlobalEventType::PlayerStopMoved;
}