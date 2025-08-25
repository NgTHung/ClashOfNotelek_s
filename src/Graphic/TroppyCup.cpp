#include "Graphic/TroppyCup.hpp"

#include "Resources/ResourcesManager.hpp"
#include "Utility/Environment.hpp"

TroppyCup::TroppyCup(): GraphicBase(sf::Vector2f(0,0)),m_Sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("TroppyCup.png"))
{
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(Environment::ScreenResolution)));
    m_Sprite.setScale(sf::Vector2f(0,0));
    m_Sprite.setOrigin(sf::Vector2f(Environment::ScreenResolution)/2.f);
}

void TroppyCup::SetScale(const sf::Vector2f& scale)
{
    m_Sprite.setScale(scale);
}

void TroppyCup::SetPosition(const sf::Vector2f& position)
{
     m_Sprite.setPosition(position);
}

void TroppyCup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite);
}

GlobalEventType TroppyCup::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool TroppyCup::Update(const sf::Time& DT)
{

    if (isActive)
    {
        sf::Vector2f curScale = m_Sprite.getScale();
        if (curScale.x >= 1 || curScale.y >= 1)
            return false;
        m_Sprite.setScale(curScale + m_ScaleSpeed);

    }
    return true;
}
void TroppyCup::Active()
{
    isActive = true;
}
bool TroppyCup::HandleInput(const sf::Event&)
{
    return true;
}
