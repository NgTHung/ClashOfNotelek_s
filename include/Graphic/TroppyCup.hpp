#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Graphic/Base.hpp"
class TroppyCup: public GraphicBase
{
private:
    bool isActive = false;
sf::Vector2f m_ScaleSpeed = sf::Vector2f(0.005f,0.005f);
    sf::Sprite m_Sprite;
    int m_TimeCounter = 0;
public:
    TroppyCup();
    ~TroppyCup() override = default;
    void SetScale(const sf::Vector2f& scale) override;
    void SetPosition(const sf::Vector2f& position) override;
    void Active();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    bool HandleInput(const sf::Event&) override;
};