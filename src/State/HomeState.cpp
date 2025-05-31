#include "State/HomeState.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Engine/Engine.hpp"

HomeState::HomeState(const Engine &g_Engine)
{
    // Need to edit
    sf::Vector2f Position = static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f;
    sf::IntRect IntRect = {{0, 0}, {32, 32}};
    sf::Vector2f Factors = {2.5, 2.5};

    this->Notelek.SetPosition(Position);
    this->Notelek.SetIntRect(IntRect);
    this->Notelek.SetScale(Factors);

    this->activeKey.clear();
}

bool HomeState::Render(sf::RenderTarget &Renderer) const
{
    this->Notelek.Render(Renderer);
    return true;
}

bool HomeState::HandleEvent(const std::optional<sf::Event> Event)
{
    if (const auto *keyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        this->activeKey.insert(keyPressed->code);
    }
    if (const auto *keyPressed = Event->getIf<sf::Event::KeyReleased>())
    {
        this->activeKey.erase(keyPressed->code);
    }

    for (auto key : activeKey)
    {
        switch (key)
        {
        case sf::Keyboard::Key::Right:
        {
            this->Notelek.Next();
            sf::Vector2f Position = this->Notelek.GetPosition();
            Position.x += 2.5;
            this->Notelek.SetPosition(Position);
            break;
        }
        case sf::Keyboard::Key::Left:
        {
            this->Notelek.Next();
            sf::Vector2f Position = this->Notelek.GetPosition();
            Position.x -= 2.5;
            this->Notelek.SetPosition(Position);
            break;
        }

        case sf::Keyboard::Key::Down:
        {
            this->Notelek.Next();
            sf::Vector2f Position = this->Notelek.GetPosition();
            Position.y += 2.5;
            this->Notelek.SetPosition(Position);
            break;
        }
        case sf::Keyboard::Key::Up:
        {
            this->Notelek.Next();
            sf::Vector2f Position = this->Notelek.GetPosition();
            Position.y -= 2.5;
            this->Notelek.SetPosition(Position);
            break;
        }
        default:
            this->Notelek.Init();
            break;
        }
    }

    return true;
}

bool HomeState::HandleInput()
{
    return true;
}

bool HomeState::FixLagUpdate(const sf::Time &DT)
{
    return true;
}

bool HomeState::Update(const sf::Time &DT)
{
    return true;
}