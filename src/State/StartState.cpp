#include "State/StartState.hpp"
#include "Resources/ResourcesManager.hpp"

StartState::StartState(const sf::RenderWindow &Window) : Names({"TTP", "TLTH", "BBQ"}), Name(ResourcesManager::GetManager()->GetFontHolder().GetFont("arial.ttf"))
{
    Index = 0;
    Name.setString(Names[Index]);
    Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Name.setFillColor(sf::Color::Blue);
    TextBound = Name.getLocalBounds();
    Name.setOrigin(TextBound.getCenter());
    Name.setPosition(static_cast<sf::Vector2f>(Window.getSize()) / 2.f);
}

bool StartState::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(Name);
    return true;
}

bool StartState::HandleEvent(const std::optional<sf::Event> Event)
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

bool StartState::HandleInput()
{
    return true;
}

bool StartState::FixLagUpdate(const sf::Time &DT)
{
    return true;
}

bool StartState::Update(const sf::Time &DT)
{
    return true;
}