#include "State/StartScreen.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Enviroment.hpp"
#include "State/HomeScreen.hpp"
// Define start State

StartScreen::StartScreen(Engine &g_Engine) : Screen(g_Engine), m_StartButton(g_Engine, static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f, std::string("Start Playing")),m_PlayButton(g_Engine, static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f, ResourcesManager::GetManager().GetTextureHolder().GetTexture("play_button.png"))
{
    // m_StartButton.SetOnClick([this]()
    //                          { this->m_Engine.PushState<HomeScreen>(this->m_Engine); });
    m_PlayButton.SetOnClick([this]()
                             { this->m_Engine.PushState<HomeScreen>(this->m_Engine); });
}

bool StartScreen::Render(sf::RenderTarget &Renderer)
{
    //Renderer.draw(m_StartButton);
    Renderer.draw(m_PlayButton);
    return true;
}

bool StartScreen::HandleInput(const std::optional<sf::Event> Event)
{
    return m_PlayButton.HandleInput(Event.value());
    //return m_StartButton.HandleInput(Event.value());
}

bool StartScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool StartScreen::FixLagUpdate(const sf::Time &DT)
{
    return m_PlayButton.FixLagUpdate(DT);
    //return m_StartButton.FixLagUpdate(DT);
}

bool StartScreen::Update(const sf::Time &DT)
{
    return m_PlayButton.Update(DT);
    //return m_StartButton.Update(DT);
}
