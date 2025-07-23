#include "State/HomeScreen.hpp"

#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
// Define start State

HomeScreen::HomeScreen(Engine &g_Engine) : Screen(g_Engine), m_Character(g_Engine), m_MapTexture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("test_map.png")),m_Slime(g_Engine)
{

    m_MapTexture.setScale(Enviroment::SpriteScalingFactor);
    m_MapTexture.setPosition(sf::Vector2f(0,0));
}

bool HomeScreen::Render(sf::RenderTarget &Renderer)
{
    Renderer.draw(m_MapTexture);
    Renderer.draw(m_Character);
    Renderer.draw(m_Slime);
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
    m_Engine.SetCenter(sf::Vector2f(m_Character.GetPosition().x + Enviroment::CenterPointofPlayer.x,m_Character.GetPosition().y + Enviroment::CenterPointofPlayer.y));
    return m_Character.Update(DT);
}
