#include "Graphic/SmokeVFX.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Environment.hpp"

HitSmokeVFX::HitSmokeVFX():GraphicBase(sf::Vector2f(Environment::SpriteSize)), m_Sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("HitSmokeVFX.png"))
{
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(64,64)));
    m_Sprite.setOrigin(sf::Vector2f(31,64));
    m_Sprite.setScale(Environment::SpriteScalingFactor);
    m_Index = 0;
}

void HitSmokeVFX::Active(sf::Vector2f Pos,sf::Vector2f Direction)
{
    m_Active = true;
    m_Sprite.setPosition(Pos);
    m_Direction = Direction;

}

GlobalEventType HitSmokeVFX::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool HitSmokeVFX::Update(const sf::Time &DT)
{
    if (!m_Active) return false;
    m_MiliSecondUpdate += DT.asMilliseconds();
    if (m_MiliSecondUpdate >= 60)
    {
        m_MiliSecondUpdate -= 60;
        m_Index = (m_Index + 1) % 5;
        if (m_Index == 4)
        {
            m_MiliSecondUpdate = 0;
            m_Active = false;
        }
    }
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_Index*64,0),sf::Vector2i(64,64)));
    float angle = std::atan2(m_Direction.y, m_Direction.x) * 180.f / 3.14159265f;
    m_Sprite.setRotation(sf::degrees(angle + 90.0f));
    return false;
}

bool HitSmokeVFX::HandleInput(const sf::Event&)
{
    return false;
}
bool HitSmokeVFX::IsActive() const
{
    return m_Active;
}


void HitSmokeVFX::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite);
}

//======================================================================================

DeadSmokeVFX::DeadSmokeVFX():GraphicBase(sf::Vector2f(Environment::SpriteSize)), m_Sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("DeadSmokeVFX.png"))
{
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(64,64)));
    m_Sprite.setOrigin(sf::Vector2f(32,32));
    m_Sprite.setScale(Environment::SpriteScalingFactor);
    m_Index = 0;
}

void DeadSmokeVFX::Active(sf::Vector2f Pos)
{
    m_Active = true;
    m_Sprite.setPosition(Pos);

}

GlobalEventType DeadSmokeVFX::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool DeadSmokeVFX::Update(const sf::Time &DT)
{
    if (!m_Active) return false;
    m_MiliSecondUpdate += DT.asMilliseconds();
    if (m_MiliSecondUpdate >= 40)
    {
        m_MiliSecondUpdate -= 40;
        m_Index = (m_Index + 1) % 7;
        if (m_Index == 6)
        {
            m_MiliSecondUpdate = 0;
            m_Active = false;
        }
    }
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_Index*64,0),sf::Vector2i(64,64)));
    return false;
}

bool DeadSmokeVFX::HandleInput(const sf::Event&)
{
    return false;
}
bool DeadSmokeVFX::IsActive() const
{
    return m_Active;
}


void DeadSmokeVFX::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite);
}



