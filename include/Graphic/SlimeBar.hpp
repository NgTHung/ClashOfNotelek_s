#pragma once
#include <SFML/Graphics.hpp>
#include <Graphic/Base.hpp>
#include <iostream>

#include "Utility/Environment.hpp"

class SlimeBar: public  GraphicBase
{
private:

    int m_maxslime = Environment::NumberSlimeToKilled;
    sf::RectangleShape m_BackGround;
    sf::RectangleShape m_Bar;
    int m_SlimeHasKilled;

    sf::Vector2f m_Size = sf::Vector2f(650,30);
    sf::Sprite m_Slime;
public:
    SlimeBar();
    ~SlimeBar() override = default;
    void KillASlime();
    bool IsWin();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void SetPosition(const sf::Vector2f& pos) override;

    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    bool HandleInput(const sf::Event&) override;
};
