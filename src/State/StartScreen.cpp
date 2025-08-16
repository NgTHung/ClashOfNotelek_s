#include "State/StartScreen.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Enviroment.hpp"
#include "State/HomeScreen.hpp"
// Define start State

StartScreen::StartScreen(Engine& g_Engine) : Screen(g_Engine),
                                             m_ExitButton(
                                                 g_Engine,
                                                 static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()),
                                                 ResourcesManager::GetManager().GetTextureHolder().
                                                 GetTexture("Exit_button.png")),
                                             m_PlayButton(
                                                 g_Engine,
                                                 static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()),
                                                 ResourcesManager::GetManager().GetTextureHolder().GetTexture(
                                                     "play_button.png"))
{
    // m_StartButton.SetOnClick([this]()
    //                          { this->m_Engine.PushState<HomeScreen>(this->m_Engine); });
    m_PlayButton.SetOnClick([this]()
    {
        this->m_Engine.PushState<HomeScreen>(this->m_Engine);
    });
    m_ExitButton.SetOnClick([this]()
    {
        this->m_Engine.CloseWindow();
    });
    m_PlayButton.SetPosition(sf::Vector2f(m_Engine.GetWindow().getSize().x/2.f,m_Engine.GetWindow().getSize().y / 3.f));
    m_ExitButton.SetPosition(sf::Vector2f(m_Engine.GetWindow().getSize().x/2.f,m_Engine.GetWindow().getSize().y *2.f/ 3.f));
}

bool StartScreen::Render(sf::RenderTarget& Renderer)
{
    //Renderer.draw(m_StartButton);
    Renderer.draw(m_PlayButton);
    Renderer.draw(m_ExitButton);
    return true;
}

bool StartScreen::HandleInput(const std::optional<sf::Event> Event)
{
    m_PlayButton.HandleInput(Event.value());
    m_ExitButton.HandleInput(Event.value());
    return true;
    //return m_StartButton.HandleInput(Event.value());
}

bool StartScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool StartScreen::FixLagUpdate(const sf::Time& DT)
{
    m_PlayButton.FixLagUpdate(DT);
    m_ExitButton.FixLagUpdate(DT);
    return true;
    //return m_StartButton.FixLagUpdate(DT);
}

bool StartScreen::Update(const sf::Time& DT)
{
    m_PlayButton.Update(DT);
    m_ExitButton.Update(DT);
    return true;
    //return m_StartButton.Update(DT);
}
