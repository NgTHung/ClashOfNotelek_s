#include "State/HomeScreen.hpp"

#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
// Define start State

HomeScreen::HomeScreen(Engine &g_Engine)
    : Screen(g_Engine), m_Character(g_Engine),
      m_MapTexture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("test_map.png")),
      m_Slime(g_Engine)
{

    m_MapTexture.setScale(Enviroment::MapScalingFactor);
    m_MapTexture.setPosition(sf::Vector2f(0, 0));
    m_Enemy.clear();
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
    m_Engine.SetCenter(sf::Vector2f(m_Character.GetPosition().x + Enviroment::CenterPointofPlayer.x, m_Character.GetPosition().y + Enviroment::CenterPointofPlayer.y));
    return m_Character.Update(DT);
}


//Enemy function
void HomeScreen::SpawnEnemy(Engine &g_Engine){
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    int num = distrib(gen);

    Enemy * fac_Enemy;
    for (int i = 0; i < num; i ++){
        std::uniform_int_distribution<> count(0, EnemyTypeCount - 1);
        EnemyType type = static_cast<EnemyType>(count(gen));

        switch (type)
        {
        case EnemyType::slime:
            fac_Enemy = new Slime(g_Engine);
            break;
        default:
            break;
        }

        // random position to spawn
        // set position for each enemy
        // fac_Enemy->SetPosition(n_Position); need to edit

        m_Enemy.emplace_back(fac_Enemy);
    }
}