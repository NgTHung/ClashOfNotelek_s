#include "Engine/Engine.hpp"
#include "State/WinScreen.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Environment.hpp"


WinScreen::WinScreen(Engine& g_Engine): Screen(g_Engine), m_ExitButton(
                                            g_Engine,
                                            static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()),
                                            ResourcesManager::GetManager().GetTextureHolder().
                                            GetTexture("Exit_button.png")),
                                        m_ReplayButton(
                                            g_Engine,
                                            static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()),
                                            ResourcesManager::GetManager().GetTextureHolder().
                                            GetTexture("PlayAgain_button.png")),
                                        m_WindowTexture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("WinBackGround.png"))

{

    m_ReplayButton.SetOnClick([this]()
    {
      this->m_Engine.PopState();
    });
    m_ExitButton.SetOnClick([this]()
    {
        this->m_Engine.CloseWindow();
    });
    m_TroppyCup.Active();
    m_ReplayButton.SetPosition(sf::Vector2f(g_Engine.GetWindow().getSize().x/2.f ,g_Engine.GetWindow().getSize().y / 3.f ));
    m_ExitButton.SetPosition(sf::Vector2f(g_Engine.GetWindow().getSize().x/2.f ,g_Engine.GetWindow().getSize().y *2.f/ 3.f ));
    m_TroppyCup.SetPosition(sf::Vector2f(Environment::ScreenResolution)/2.f);
    m_Engine.stopBackGroundMusic();
    m_Engine.StopWalkingMusic();
}

bool WinScreen::Render(sf::RenderTarget& Renderer)
{
    Renderer.draw(m_WindowTexture);
    Renderer.draw(m_TroppyCup);
    if (Renderbutton)
    {
        Renderer.draw(m_ReplayButton);
        Renderer.draw(m_ExitButton);
    }
    return true;
}

bool WinScreen::Update(const sf::Time& DT)
{
    if (!playmusic)
    {
        m_Engine.PlaySound("winMusic");
        playmusic = true;
    }
    if (!m_TroppyCup.Update(DT))
        Renderbutton = true;
    m_Engine.ResetView();
    if (Renderbutton)
    {
        m_ReplayButton.Update(DT);
        m_ExitButton.Update(DT);
    }
    return true;
}

bool WinScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return false;
}

bool WinScreen::HandleInput(const std::optional<sf::Event> Event)
{
    if (Renderbutton)
    {
        m_ReplayButton.HandleInput(Event.value());
        m_ExitButton.HandleInput(Event.value());
    }
    return true;
}



