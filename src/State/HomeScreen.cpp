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

    m_MapTexture.setScale(Enviroment::SpriteScalingFactor);
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
    this->CameraProcess();
    return m_Character.Update(DT);
}

void HomeScreen::CameraProcess()
{
    sf::View view = m_Engine.GetWindow().getView();
    sf::Vector2f ViewSize = view.getSize();
    sf::Vector2f CenterPoint = sf::Vector2f(m_Character.GetPosition().x + Enviroment::CenterPointOfPlayer.x * Enviroment::SpriteScalingFactor.x,m_Character.GetPosition().y + Enviroment::CenterPointOfPlayer.y* Enviroment::SpriteScalingFactor.y);
    sf::Vector2f PlayerPosition = CenterPoint;
    sf::Vector2f MapSize = m_MapTexture.getGlobalBounds().size;
    sf::Vector2f HaftView = sf::Vector2f(ViewSize.x / 2, ViewSize.y / 2);

    if (MapSize.x > ViewSize.x)
        CenterPoint.x = std::clamp(PlayerPosition.x, HaftView.x, MapSize.x - HaftView.x);
    else
        CenterPoint.x = MapSize.x / 2.f;

    if (MapSize.y > ViewSize.y)
        CenterPoint.y = std::clamp(PlayerPosition.y, HaftView.y, MapSize.y - HaftView.y);
    else
        CenterPoint.y = MapSize.y / 2.f;

    view.setCenter(CenterPoint);
    m_Engine.SetView(view);
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