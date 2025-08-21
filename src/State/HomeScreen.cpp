#include "State/HomeScreen.hpp"

#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "State/WinScreen.hpp"
#include "Utility/Logger.hpp"
// Define start State

HomeScreen::HomeScreen(Engine &g_Engine)
    : Screen(g_Engine),m_Character(g_Engine),
      m_MapTexture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("test_map.png")),
       m_Water(g_Engine),m_Menu(g_Engine,*this)
{
    //m_Walls.push_back(std::make_shared<Wall>(this->m_Engine,sf::Vector2f(0,0),sf::Vector2f(26,299)));
    m_MapTexture.setScale(sf::Vector2f(10,10));
    m_MapTexture.setPosition(sf::Vector2f(0, 0));

    for (auto WaterWall : Environment::WaterWall)
    {
        sf::Vector2f Pos = sf::Vector2f(WaterWall.position.x * m_MapTexture.getScale().x,WaterWall.position.y * m_MapTexture.getScale().y);
        sf::Vector2f Size = sf::Vector2f(WaterWall.size.x * m_MapTexture.getScale().x,WaterWall.size.y * m_MapTexture.getScale().y);
        m_Water.AddWall(Pos,Size);
    }

    for (auto box : Environment::BoxPositions)
    {
        std::shared_ptr<Box> tmp = std::make_shared<Box>(g_Engine,sf::Vector2f(Environment::SpriteSize.x,Environment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(box.x*m_MapTexture.getScale().x,box.y*m_MapTexture.getScale().y));
        m_Boxes.push_back(tmp);
    }

    for (auto tinyygrasspos: Environment::TinyGrassPositions)
    {
        std::shared_ptr<TinyGrass> tmp = std::make_shared<TinyGrass>(g_Engine,sf::Vector2f(Environment::SpriteSize.x,Environment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(tinyygrasspos.x*m_MapTexture.getScale().x,tinyygrasspos.y*m_MapTexture.getScale().y));
        m_TinyGrasses.push_back(tmp);
    }

    for (auto Grasspos: Environment::GrassPositions)
    {
        std::shared_ptr<Grass> tmp = std::make_shared<Grass>(g_Engine,sf::Vector2f(Environment::SpriteSize.x,Environment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(Grasspos.x*m_MapTexture.getScale().x,Grasspos.y*m_MapTexture.getScale().y));
        m_Grasses.push_back(tmp);
    }

    for (auto TreePos: Environment::TreePositions)
    {
        std::shared_ptr<Tree> tmp = std::make_shared<Tree>(g_Engine,sf::Vector2f(Environment::SpriteSize.x,Environment::SpriteSize.y));
        tmp->SetPosition(sf::Vector2f(TreePos.x*m_MapTexture.getScale().x,TreePos.y*m_MapTexture.getScale().y));
        m_Trees.push_back(tmp);
    }


    for (const auto& wall : m_Walls)
        wall->SetScale(sf::Vector2f(10,10));
    m_Enemy.clear();
    m_vDT.reserve(Environment::FrameLimit + 1);
    m_FPS.setFillColor(sf::Color::Black);
    m_Overlay.setFillColor(sf::Color(0,0,0,150));
    m_Overlay.setSize(sf::Vector2f(Environment::ScreenResolution));
    m_Menu.SetOrigin(sf::Vector2f(150,125));
}

void HomeScreen::PauseGame()
{
    isPause = !isPause;
}

bool HomeScreen::Render(sf::RenderTarget &Renderer)
{
    Renderer.draw(m_MapTexture);

    m_RenderQueue.clear();
    m_RenderQueue.push_back(&m_Character);

    for (const auto& box : this->m_Boxes)
        m_RenderQueue.push_back(box.get());
    for (const auto& tinygrass: m_TinyGrasses)
        m_RenderQueue.push_back(tinygrass.get());
    for (const auto& grass: m_Grasses)
        m_RenderQueue.push_back(grass.get());
    for (const auto& tree : m_Trees)
        m_RenderQueue.push_back(tree.get());
    for (const auto& enemy : m_Enemy)
        m_RenderQueue.push_back(enemy.get());

    sort(m_RenderQueue.begin(), m_RenderQueue.end(), [](GraphicBase *lhs, GraphicBase *rhs)
    {
        return lhs->GetYAxisPoint() < rhs->GetYAxisPoint();
    });

    for (auto renderthing : m_RenderQueue)
        Renderer.draw(*renderthing);
    Renderer.draw(m_FPS);
    Renderer.draw(m_Character.GetPlayerHealthBar());
    if (isPause)
    {
        Renderer.draw(m_Overlay);
        Renderer.draw(m_Menu);
    }

    return true;
}

bool HomeScreen::HandleInput(const std::optional<sf::Event> Event)
{
    if (!Event.has_value()) return true;

    if (const auto *KeyPressed = Event->getIf<sf::Event::KeyPressed>())
    {
        if ( KeyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            PauseGame();
        }
    }
    if (!isPause)
        return m_Character.HandleInput(Event.value());
    else
    {
        m_Menu.HandleInput(Event.value());
        return true;
    }

}

bool HomeScreen::HandleEvent(std::shared_ptr<BaseEvent> Event)
{

    return false;
}

bool HomeScreen::Update(const sf::Time &DT)
{

    if (isPause)
    {
        m_Overlay.setPosition(m_Engine.GetWindow().getView().getCenter() - m_Engine.GetWindow().getView().getSize()/2.f);
        m_Menu.SetPosition(m_Engine.GetWindow().getView().getCenter());
        m_Menu.Update(DT);
        return false;
    }
    if (IsWinGame())
    {
        m_Engine.PushState(std::make_unique<WinScreen>(m_Engine));
    }

    for (const auto& tinygrass: m_TinyGrasses)
        tinygrass->Update(DT);
    for (const auto& grass : m_Grasses)
        grass->Update(DT);
    for (const auto& enemy : m_Enemy)
        enemy->Update(DT);
    fps += DT.asSeconds()/ Environment::FrameLimit;
    m_vDT.push_back(DT.asSeconds());
    if (m_vDT.size() > Environment::FrameLimit)
    {
        fps -= m_vDT.front() / Environment::FrameLimit;
        m_vDT.erase(m_vDT.begin());
    }
    m_FPS.setString(std::format("FPS: {:.2f}", 1.f / fps));
    m_FPS.setPosition(m_Character.GetPosition());
    //delete dead enemy
    for (const auto& enemy : m_Enemy)
    {
        if (enemy->GetState() == EnemyState::CanDelete)
        {
            if (enemy->GetType() == EnemyType::slime)
                m_Character.HasKilledaSlime();
            m_Engine.GetCollisionSystem().RemoveCollidable(enemy->GetID(),Environment::AttackableLayer);
            m_Engine.GetCollisionSystem().RemoveCollidable(enemy->GetID(),Environment::EnemyAttackLayer);
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
    sf::Vector2f CenterPoint = sf::Vector2f(m_Character.GetPosition().x + Environment::CenterPointOfPlayer.x * Environment::SpriteScalingFactor.x,m_Character.GetPosition().y + Environment::CenterPointOfPlayer.y* Environment::SpriteScalingFactor.y);
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


bool HomeScreen::IsWinGame()
{
    if (m_Character.GetNumberofSlimeHasKilled() >= Environment::NumberSlimeToKilled)
        return true;
    return false;
}

//Enemy function
void HomeScreen::SpawnEnemy(){
    std::random_device rd; 
    std::mt19937 gen(rd());
//int num = distrib(gen);
    int num = 2;
    Enemy * fac_Enemy;
    for (int i = 0; i < num; i ++){
        std::uniform_int_distribution<> count(0, static_cast<int>(EnemyType::EnemyTypeCount) - 1);
        auto type = static_cast<EnemyType>(count(gen));

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
        std::uniform_int_distribution<> distribx(0, Environment::ScreenResolution.x - 1);
        int x = distribx(gen);
        //std::uniform_int_distribution<> distriby(0, m_MapTexture.getGlobalBounds().size.y);
        std::uniform_int_distribution<> distriby(0, Environment::ScreenResolution.y - 1);
        int y = distriby(gen);
        sf::Vector2f pos = {(float)x, (float)y};
        if (m_Engine.GetCollisionSystem().IsFree(pos,*fac_Enemy,Environment::MapEntityCollisionLayer))
        {
            fac_Enemy->SetPosition(pos);
            fac_Enemy->SetStartPosition(pos);
            m_Enemy.emplace_back(fac_Enemy);
        }
    }
}