#include "Graphic/HealthBar.hpp"
HealthBar::HealthBar(): m_Offset(sf::Vector2f{0,0})
{
    m_MaxHealth = 0;
    m_BackgroundBar.setSize(m_Size);
    m_HealthBar.setSize(m_Size);
    m_HealthBar.setFillColor(sf::Color::Green);
    m_BackgroundBar.setFillColor(sf::Color::Transparent);
    m_BackgroundBar.setOutlineColor(sf::Color::Red);
    m_BackgroundBar.setOutlineThickness(1);
}

void HealthBar::SetMaxHealth(const float& MaxHealth)
{
    m_MaxHealth = MaxHealth;
}


void HealthBar::Update(const float& CurrentHealth, const sf::Vector2f& Pos)
{
    m_BackgroundBar.setPosition(Pos);
    m_HealthBar.setPosition((Pos));

    float percent = CurrentHealth / m_MaxHealth;
    m_HealthBar.setSize({ m_Size.x * percent, m_Size.y });
}

void HealthBar::Draw(sf::RenderTarget& Target) const
{
    Target.draw(m_HealthBar);
    Target.draw(m_BackgroundBar);
}



