#include "State/StartScreen.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Enviroment.hpp"
#include "State/HomeScreen.hpp"
// Define start State

StartScreen::StartScreen(Engine &g_Engine) : Screen(g_Engine), m_StartButton(g_Engine, (sf::Vector2f)g_Engine.GetWindow().getSize() / 2.f, std::string("Start Playing"))
{
    m_StartButton.SetOnClick([this]()
                             { this->m_Engine.PushState<HomeScreen>(this->m_Engine); });
}

bool StartScreen::Render(sf::RenderTarget &Renderer)
{
    m_StartButton.Render(Renderer);
    return true;
}

bool StartScreen::HandleInput(const std::optional<sf::Event> Event)
{
    return m_StartButton.HandleInput(Event.value());
}

bool StartScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool StartScreen::FixLagUpdate(const sf::Time &DT)
{
    return m_StartButton.FixLagUpdate(DT);
}

bool StartScreen::Update(const sf::Time &DT)
{
    return m_StartButton.Update(DT);
}
