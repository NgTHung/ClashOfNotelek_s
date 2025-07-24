#pragma once
#include "State/Screen.hpp"
#include "Graphic/Sprite.hpp"
#include <SFML/Graphics.hpp>

#include "Graphic/Enemy.hpp"
#include "Graphic/Wall.hpp"

#include <random>

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
    // Player function
    // Enemy function
    void SpawnEnemy(Engine &g_Engine);
private:
    Character m_Character;
    std::vector<std::shared_ptr<Wall>> m_Walls;
    std::vector<std::shared_ptr<Wall>> m_BoundingBoxes;
    sf::Sprite m_MapTexture;
    Slime m_Slime;
    std::vector<std::shared_ptr<Enemy>> m_Enemy;
};
