#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Graphic/Base.hpp"
class PlayerHealthBarFace: public GraphicBase
{
public:
    PlayerHealthBarFace();
    ~PlayerHealthBarFace() override = default;
    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    void SetPosition(const sf::Vector2f& Pos) override;
    sf::Vector2f GetPosition() const override;
    void BeAttack();
    bool HandleInput(const sf::Event&) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
     float GetYAxisPoint() override;
private:
    bool m_Flash = false;
    int m_Index = 0;
    int m_MillisecondsPerFrame = 150;
    int m_LastUpdate = 0;
    sf::Sprite m_sprite;

};

class PlayerHealthBar: public GraphicBase
{
private:
    sf::Vector2f m_Size;
    PlayerHealthBarFace m_Face;
    sf::RectangleShape m_BackgroundBar;
    sf::RectangleShape m_HealthBar;
    float m_MaxHealth;
    float m_CurrentHealth;
public:
    PlayerHealthBar();
    void SetMaxHealth(const float& MaxHealth);
    void SetCurrentHealth(const float& CurrentHealth);
    void SetPosition(const sf::Vector2f& Pos) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    void BeAttack();
    bool HandleInput(const sf::Event&) override;
    float GetYAxisPoint() override;
};