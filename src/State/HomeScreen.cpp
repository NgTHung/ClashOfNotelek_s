#include "State/HomeScreen.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Engine/Engine.hpp"

HomeScreen::HomeScreen(Engine &g_Engine) : Screen(g_Engine)
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

bool HomeScreen::Render(sf::RenderTarget &Renderer)
{
    this->Notelek.Render(Renderer);
    return true;
}

bool HomeScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    // if (const auto *keyPressed = Event->getIf<sf::Event::KeyPressed>())
    // {
    //     this->activeKey.insert(keyPressed->scancode);
    // }
    // if (const auto *keyReleased = Event->getIf<sf::Event::KeyReleased>())
    // {
    //     this->activeKey.erase(keyReleased->scancode);
    // }
    return true;
}

bool HomeScreen::HandleInput()
{
    return true;
}

bool HomeScreen::FixLagUpdate(const sf::Time &DT)
{
    return true;
}

bool HomeScreen::IsDashTurn() const
{
    return true;
}

bool HomeScreen::Update(const sf::Time &DT)
{
    if (this->activeKey.empty())
    {
        this->Notelek.Init();
    }
    else
    {
        float moveX = 0.0f, moveY = 0.0f;
        for (sf::Keyboard::Scancode key : activeKey)
        {
            switch (key)
            {
            case sf::Keyboard::Scancode::D:
                moveX += 2.5;
                break;
            case sf::Keyboard::Scancode::A:
                moveX -= 2.5;
                break;

            case sf::Keyboard::Scancode::S:
                moveY += 2.5;
                break;
            case sf::Keyboard::Scancode::W:
                moveY -= 2.5;
                break;
            case sf::Keyboard::Scancode::Space:
                moveY = (moveY * 5) * IsDashTurn();
                moveX = (moveX * 5) * IsDashTurn();
            default:
                break;
            }
        }
        if (moveX != 0.0f || moveY != 0.0f)
        {
            sf::Vector2f Position = this->Notelek.GetPosition();
            Position.x += moveX;
            Position.y += moveY;
            this->Notelek.Next();
            this->Notelek.SetPosition(Position);
        }
    }

    return true;
}