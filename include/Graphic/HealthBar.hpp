#pragma once
#include "Graphic/Base.hpp"

class HealthBar{
private:
    sf::RectangleShape m_BackgroundBar;
    sf::RectangleShape m_HealthBar;
    float m_MaxHealth;

    sf::Vector2f m_Size = sf::Vector2f{100.0f,10.0f};
    sf::Vector2f m_Offset;

public:
    HealthBar();

    void SetMaxHealth(const float& MaxHHealth);

    void Update(const float& CurrentHealth,const sf::Vector2f& Pos);

    void Draw(sf::RenderTarget& Target) const;

    ~HealthBar() = default;
};