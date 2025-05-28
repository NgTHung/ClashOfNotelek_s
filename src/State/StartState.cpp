#include "State/StartState.hpp"
#include "Resources/ResourcesManager.hpp"

StartState::StartState(const sf::RenderWindow &Window) : m_Names({"TTP", "TLTH", "BBQ"}), m_Name(ResourcesManager::GetManager()->GetFontHolder().GetFont("arial.ttf"))
{
    Index = 0;
    m_Name.setString(m_Names[Index]);
    m_Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_Name.setFillColor(sf::Color::Blue);
    m_TextBound = m_Name.getLocalBounds();
    m_Name.setOrigin(m_TextBound.getCenter());
    m_Name.setPosition(static_cast<sf::Vector2f>(Window.getSize()) / 2.f);
}

bool StartState::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(m_Name);
    return true;
}

bool StartState::HandleEvent(const std::optional<sf::Event> Event)
{
    if (const auto *keyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
        {
            (Index += 1) %= 3;
            m_Name.setString(m_Names[Index]);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::W)
        {
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