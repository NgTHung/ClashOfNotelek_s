#pragma once
#include "Graphic/Base.hpp"
#include "Utility/Environment.hpp"
class HitSmokeVFX: public GraphicBase
{
private:
    sf::Sprite m_Sprite;
    bool m_Active = false;
    int m_MiliSecondUpdate = 0;
    sf::Vector2f m_Direction;
    int m_Index = 0;

public:
    HitSmokeVFX();
    void Active(sf::Vector2f Pos,sf::Vector2f Direction);
    bool IsActive() const;
    bool Update(const sf::Time& DT) override;
    bool HandleInput(const sf::Event&) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    ~HitSmokeVFX() override = default;
};

class DeadSmokeVFX: public GraphicBase
{
private:
    sf::Sprite m_Sprite;
    bool m_Active = false;
    int m_MiliSecondUpdate = 0;
    int m_Index = 0;

public:
    DeadSmokeVFX();
    void Active(sf::Vector2f Pos);
    bool IsActive() const;
    bool Update(const sf::Time& DT) override;
    bool HandleInput(const sf::Event&) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    ~DeadSmokeVFX() override = default;
};