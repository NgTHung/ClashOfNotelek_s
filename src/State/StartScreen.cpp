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
