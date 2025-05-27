#include "State/HomeState.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Engine/Engine.hpp"

HomeState::HomeState(const Engine &g_Engine) : Names({"HIHI", "HOHO", "HEHE"}), Name(ResourcesManager::GetManager()->GetFontHolder().GetFont("arial.ttf"))
{
    Index = 0;
    Name.setString(Names[Index]);
    Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Name.setFillColor(sf::Color::Blue);
    TextBound = Name.getLocalBounds();
    Name.setOrigin(TextBound.getCenter());
    Name.setPosition(static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f);
}

bool HomeState::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(Name);
    return true;
}

bool HomeState::HandleEvent(const std::optional<sf::Event> Event)
{
    if (const auto *keyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
        {
            (Index += 1) %= 3;
            Name.setString(Names[Index]);
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