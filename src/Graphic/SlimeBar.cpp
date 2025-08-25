#include "Graphic/SlimeBar.hpp"

#include "Resources/ResourcesManager.hpp"

SlimeBar::SlimeBar(): GraphicBase(sf::Vector2f(0,0)),m_Slime(ResourcesManager::GetManager().GetTextureHolder().GetTexture("Slime.png"))
{
    m_BackGround.setSize(m_Size);
    m_Bar.setSize(m_Size);
    m_Bar.setFillColor(sf::Color(168, 202, 88));
    m_Slime.setTextureRect(sf::IntRect(sf::Vector2i(0,32),sf::Vector2i(32,32)));
    m_Slime.setScale(sf::Vector2f(2.5,2.5));
    m_Slime.setOrigin(sf::Vector2f(15,27));
    m_BackGround.setFillColor(sf::Color(138, 87, 78));
    m_BackGround.setOutlineColor(sf::Color(99, 66, 67));
    m_BackGround.setOutlineThickness(5);
    m_SlimeHasKilled = 0;
}

void SlimeBar::KillASlime()
{
    m_SlimeHasKilled++;
}


void SlimeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_BackGround);
    target.draw(m_Bar);
    target.draw(m_Slime);
}

void SlimeBar::SetPosition(const sf::Vector2f& pos)
{
    int offsetx = (Environment::ScreenResolution.x - m_Size.x)/2;
    int offsety = 10.f;
    sf::Vector2f centerpos = pos +  sf::Vector2f(offsetx, offsety);
    m_Bar.setPosition(centerpos);
    m_BackGround.setPosition(centerpos);
}

bool SlimeBar::Update(const sf::Time& DT)
{
    float percent = m_SlimeHasKilled *1.f/ m_maxslime;
    m_Bar.setSize({ m_Size.x * percent, m_Size.y});
    m_Slime.setPosition(m_Bar.getPosition() + sf::Vector2f(m_Bar.getSize().x,m_Bar.getSize().y/2));
    return true;
}

bool SlimeBar::HandleInput(const sf::Event&)
{
    return true;
}

GlobalEventType SlimeBar::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool SlimeBar::IsWin()
{
    return (m_SlimeHasKilled >= m_maxslime);
}

