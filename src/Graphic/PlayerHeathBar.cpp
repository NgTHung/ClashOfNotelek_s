#include <float.h>

#include "Graphic/PlayerHealthbar.hpp"
#include "Resources/ResourcesManager.hpp"

PlayerHealthBarFace::PlayerHealthBarFace()
        : GraphicBase(sf::Vector2f(0,0)),
          m_sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("healthbarface.png"))
{
   m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(30,30)));
    m_sprite.setScale(sf::Vector2f(4.5f,4.5f));
   Collidable::SetScale(sf::Vector2f(4.5f,4.5f));

}
void PlayerHealthBarFace::BeAttack()
{
    m_Flash = true;
}


void PlayerHealthBarFace::SetPosition(const sf::Vector2f& Pos)
{
    m_sprite.setPosition(Pos);
}
GlobalEventType PlayerHealthBarFace::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool PlayerHealthBarFace::Update(const sf::Time& DT)
{
    m_LastUpdate += DT.asMilliseconds();
    if (m_LastUpdate >= m_MillisecondsPerFrame)
    {
        m_Index = (m_Index + 1) % 6;
        m_LastUpdate -= m_MillisecondsPerFrame;
        if (m_Flash)
        {
            m_Index = 6;
            m_Flash = false;
        }
    }
    m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_Index*30,0),sf::Vector2i(30,30)));
    return true;
}

bool PlayerHealthBarFace::HandleInput(const sf::Event& DT)
{
    return true;
}

void PlayerHealthBarFace::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

float PlayerHealthBarFace::GetYAxisPoint()
{
    return FLT_MAX;
}
sf::Vector2f PlayerHealthBarFace::GetPosition() const
{
    return m_sprite.getPosition();
}


PlayerHealthBar::PlayerHealthBar(): GraphicBase(sf::Vector2f(0, 0)), m_CurrentHealth(0) {
    m_MaxHealth = 0;
    m_Size = sf::Vector2f(200, 15);
    m_BackgroundBar.setSize(m_Size);
    m_HealthBar.setSize(m_Size);
    m_HealthBar.setFillColor(sf::Color(99, 199, 77));

    m_BackgroundBar.setFillColor(sf::Color(138, 87, 78));
    m_BackgroundBar.setOutlineColor(sf::Color(99, 66, 67));
    m_BackgroundBar.setOutlineThickness(5);
}

void PlayerHealthBar::SetMaxHealth(const float& MaxHealth)
{
    m_MaxHealth = MaxHealth;
}

void PlayerHealthBar::SetCurrentHealth(const float& CurrentHealth)
{
    m_CurrentHealth = CurrentHealth;
}

GlobalEventType PlayerHealthBar::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

void PlayerHealthBar::SetPosition(const sf::Vector2f& Pos)
{
    m_Face.SetPosition(Pos);
    m_BackgroundBar.setPosition(sf::Vector2f(Pos.x + 29*m_Face.GetScale().x,Pos.y + 19*m_Face.GetScale().y));
    m_HealthBar.setPosition(sf::Vector2f(Pos.x + 29*m_Face.GetScale().x,Pos.y + 19*m_Face.GetScale().y));
}

bool PlayerHealthBar::Update(const sf::Time& DT)
{
    m_Face.Update(DT);
    float percent = m_CurrentHealth / m_MaxHealth;
    m_HealthBar.setSize({ m_Size.x * percent, m_Size.y });
    return true;
}

void PlayerHealthBar::BeAttack()
{
    m_Face.BeAttack();
}

bool PlayerHealthBar::HandleInput(const sf::Event&)
{
    return true;
}

void PlayerHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_BackgroundBar);
    target.draw(m_HealthBar);
    target.draw(m_Face);
}

float PlayerHealthBar::GetYAxisPoint()
{
    return FLT_MAX;
}


