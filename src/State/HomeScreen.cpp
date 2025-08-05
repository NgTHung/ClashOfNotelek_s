#include "State/HomeScreen.hpp"

#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
// Define start State

HomeScreen::HomeScreen(Engine &g_Engine)
    : Screen(g_Engine),m_Character(g_Engine),
      m_MapTexture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("test_map.png")),
      m_Slime(m_Character,g_Engine), m_Water(g_Engine)
{
    //m_Walls.push_back(std::make_shared<Wall>(this->m_Engine,sf::Vector2f(0,0),sf::Vector2f(26,299)));
    m_MapTexture.setScale(sf::Vector2f(10,10));
    m_MapTexture.setPosition(sf::Vector2f(0, 0));

    for (auto WaterWall : Enviroment::WaterWall)
    {
        sf::Vector2f Pos = sf::Vector2f(WaterWall.position.x * m_MapTexture.getScale().x,WaterWall.position.y * m_MapTexture.getScale().y);
        sf::Vector2f Size = sf::Vector2f(WaterWall.size.x * m_MapTexture.getScale().x,WaterWall.size.y * m_MapTexture.getScale().y);
        m_Water.AddWall(Pos,Size);
    }

    for (auto box : Enviroment::BoxPositions)
    {
        std::shared_ptr<Box> tmp = std::make_shared<Box>(g_Engine,sf::Vector2f(Enviroment::SpriteSize.x,Enviroment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(box.x*m_MapTexture.getScale().x,box.y*m_MapTexture.getScale().y));
        m_Boxes.push_back(tmp);
    }

    for (auto tinyygrasspos: Enviroment::TinyGrassPositions)
    {
        std::shared_ptr<TinyGrass> tmp = std::make_shared<TinyGrass>(g_Engine,sf::Vector2f(Enviroment::SpriteSize.x,Enviroment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(tinyygrasspos.x*m_MapTexture.getScale().x,tinyygrasspos.y*m_MapTexture.getScale().y));
        m_TinyGrasses.push_back(tmp);
    }

    for (auto Grasspos: Enviroment::GrassPositions)
    {
        std::shared_ptr<Grass> tmp = std::make_shared<Grass>(g_Engine,sf::Vector2f(Enviroment::SpriteSize.x,Enviroment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(Grasspos.x*m_MapTexture.getScale().x,Grasspos.y*m_MapTexture.getScale().y));
        m_Grasses.push_back(tmp);
    }

    for (auto TreePos: Enviroment::TreePositions)
    {
        std::shared_ptr<Tree> tmp = std::make_shared<Tree>(g_Engine,sf::Vector2f(Enviroment::SpriteSize.x,Enviroment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(TreePos.x*m_MapTexture.getScale().x,TreePos.y*m_MapTexture.getScale().y));
        m_Trees.push_back(tmp);
    }



    for (auto wall : m_Walls)
        wall->SetScale(sf::Vector2f(10,10));
    m_Enemy.clear();
}

bool HomeScreen::Render(sf::RenderTarget &Renderer)
{
    Renderer.draw(m_MapTexture);

    m_RenderQueue.clear();
    m_RenderQueue.push_back(&m_Character);
    for (auto box : this->m_Boxes)
        m_RenderQueue.push_back(box.get());
    for (auto tinygrass: m_TinyGrasses)
        m_RenderQueue.push_back(tinygrass.get());
    for (auto grass: m_Grasses)
        m_RenderQueue.push_back(grass.get());
    for (auto tree : m_Trees)
        m_RenderQueue.push_back(tree.get());
    for (auto enemy : m_Enemy)
        m_RenderQueue.push_back(enemy.get());

    sort(m_RenderQueue.begin(), m_RenderQueue.end(), [](GraphicBase *lhs, GraphicBase *rhs)
    {
        return lhs->GetYAxisPoint() < rhs->GetYAxisPoint();
    });

    for (auto renderthing : m_RenderQueue)
        Renderer.draw(*renderthing);

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

    for (auto tinygrass: m_TinyGrasses)
        tinygrass->Update(DT);
    for (auto grass : m_Grasses)
        grass->Update(DT);
    for (auto enemy : m_Enemy)
        enemy->Update(DT);

    //delete dead enemy
    for (const auto& enemy : m_Enemy)
    {
        if (enemy->GetState() == EnemyState::CanDelete)
        {
            m_Engine.GetCollisionSystem().RemoveCollidable(enemy->GetID(),Enviroment::AttackableLayer);
            m_Engine.GetCollisionSystem().RemoveCollidable(enemy->GetID(),Enviroment::PlayerCollisionLayer);
            m_Engine.GetCollisionSystem().RemoveCollidable(enemy->GetID(),Enviroment::EnemyAttackLayer);
        }
    }
    m_Enemy.erase(
    std::remove_if(m_Enemy.begin(), m_Enemy.end(),
        [](const std::shared_ptr<Enemy>& enemy)
        {
            return enemy->GetState() == EnemyState::CanDelete;
        }),
    m_Enemy.end());

    this->CameraProcess();
    m_Engine.SetView(m_Engine.GetScreenShake().GetShakeViewUpdate(DT,m_Engine.GetWindow().getView()));
    if (this->m_Enemy.size() < 2)
        this->SpawnEnemy();

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
void HomeScreen::SpawnEnemy(){
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
//int num = distrib(gen);
    int num = 2;
    Enemy * fac_Enemy;
    for (int i = 0; i < num; i ++){
        std::uniform_int_distribution<> count(0, EnemyTypeCount - 1);
        EnemyType type = static_cast<EnemyType>(count(gen));

        switch (type)
        {
        case EnemyType::slime:
            fac_Enemy = new Slime(m_Character,this->m_Engine);
            break;
        default:
            break;
        }

        // random position to spawn
        // set position for each enemy
        // fac_Enemy->SetPosition(n_Position); need to edit
       // std::uniform_int_distribution<> distribx(0, m_MapTexture.getGlobalBounds().size.x);
        std::uniform_int_distribution<> distribx(0, Enviroment::ScreenResolution.x - 1);
        int x = distribx(gen);
        //std::uniform_int_distribution<> distriby(0, m_MapTexture.getGlobalBounds().size.y);
        std::uniform_int_distribution<> distriby(0, Enviroment::ScreenResolution.y - 1);
        int y = distriby(gen);
        sf::Vector2f pos = {x, y};
        if (m_Engine.GetCollisionSystem().IsFree(pos,*fac_Enemy,Enviroment::MapEntityCollisionLayer))
        {
            fac_Enemy->SetPosition(pos);
            fac_Enemy->SetStartPosition(pos);
            m_Enemy.emplace_back(fac_Enemy);
        }
    }
}