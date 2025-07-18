#include "State/HomeScreen.hpp"
#include "Utility/Logger.hpp"
// Define start State

HomeScreen::HomeScreen(Engine &g_Engine) : Screen(g_Engine), m_Character(g_Engine), m_Wall(g_Engine, sf::Vector2f(100,100), sf::Vector2f(32.f,32.f))
{
}

bool HomeScreen::Render(sf::RenderTarget &Renderer)
{
    Renderer.draw(m_Character);
    Renderer.draw(m_Wall);
    m_Wall.DrawDebug(Renderer);
    return true;
}

bool HomeScreen::HandleInput(const std::optional<sf::Event> Event)
{
    return m_Character.HandleInput(Event.value());
}

bool HomeScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool HomeScreen::FixLagUpdate(const sf::Time &DT)
{
    return m_Character.FixLagUpdate(DT);
}

bool HomeScreen::Update(const sf::Time &DT)
{
    return m_Character.Update(DT);
}
