#pragma once
#include "State/Screen.hpp"
#include "Graphic/Sprite.hpp"
#include <SFML/Graphics.hpp>

#include "Graphic/Enemy.hpp"
#include "Graphic/Wall.hpp"
#include <random>
#include "Graphic/MapEntity.hpp"
#include "Graphic/ScreenShake.hpp"
#include "Graphic/Water.hpp"
enum EnemyType{
    slime,
    EnemyTypeCount
};

class HomeScreen : public Screen
{
public:
    HomeScreen(Engine &g_Engine);
    ~HomeScreen() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleInput(std::optional<sf::Event> Event) override;
    bool FixLagUpdate(const sf::Time &DT) override;
    bool HandleEvent(std::shared_ptr<BaseEvent> Event) override;
    void CameraProcess();
    // Player function
    // Enemy function
    void SpawnEnemy();
private:

    Character m_Character;
    std::vector<std::shared_ptr<Wall>> m_Walls;
    std::vector<std::shared_ptr<Tree>> m_Trees;
    std::vector<std::shared_ptr<Grass>> m_Grasses;
    std::vector<std::shared_ptr<TinyGrass>> m_TinyGrasses;
    std::vector<std::shared_ptr<Box>> m_Boxes;
    Water m_Water;
    std::vector<GraphicBase*> m_RenderQueue;
    sf::Sprite m_MapTexture;
    Slime m_Slime;
    std::vector<std::shared_ptr<Enemy>> m_Enemy;
    std::vector<float> m_vDT;
    float fps = 0;
    ArielText m_FPS;
};
