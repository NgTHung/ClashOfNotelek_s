#include "State/StartScreen.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Environment.hpp"
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
                                                     "play_button.png")),
                                                m_Sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("startscreen.png")), m_Grass(m_Engine,sf::Vector2f(0,0)),
                                            m_LeafFalling(m_Engine,sf::FloatRect(sf::Vector2f(0,128),sf::Vector2f(416,211)),40)
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
    m_PlayButton.SetPosition(sf::Vector2f(m_Engine.GetWindow().getSize().x/2.f,m_Engine.GetWindow().getSize().y / 3.f + 100.f));
    m_ExitButton.SetPosition(sf::Vector2f(m_Engine.GetWindow().getSize().x/2.f,m_Engine.GetWindow().getSize().y *2.f/ 3.f + 50.f));
    m_Grass.SetPosition(sf::Vector2f(431,704));
    m_Grass.SetScale(sf::Vector2f(10,10));
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(Enviroment::ScreenResolution)));
}

bool StartScreen::Render(sf::RenderTarget& Renderer)
{
    //Renderer.draw(m_StartButton);
    Renderer.draw(m_Sprite);
    Renderer.draw(m_Grass);
    Renderer.draw(m_LeafFalling);
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

bool StartScreen::Update(const sf::Time& DT)
{
    m_LastUpdate += DT.asMilliseconds();
    if (m_LastUpdate >= m_TimeperFrame)
    {
        m_index = (m_index + 1) % 5;
        m_LastUpdate -= m_TimeperFrame;
    }
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_index*Enviroment::ScreenResolution.x,0),sf::Vector2i(Enviroment::ScreenResolution)));
    m_PlayButton.Update(DT);
    m_LeafFalling.Update(DT);
    m_ExitButton.Update(DT);
    m_Grass.Update(DT);
    return true;
    //return m_StartButton.Update(DT);
}
