#pragma once
#include <SFML/Graphics.hpp>
class HitBox
{   
public:
    virtual sf::FloatRect GetGlobalBounds() const = 0;
    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual void RenderDebug(sf::RenderTarget& target) const = 0;
    virtual void SetScale(const sf::Vector2f& scale) = 0;
    virtual void SetRotation(sf::Angle angle) = 0;
    virtual std::vector<sf::Vector2f> GetTransformedPoints() = 0;
    virtual ~HitBox() = default;
};

class RectangleHitBox : public HitBox
{
private:
    sf::FloatRect m_Offset;
    sf::RectangleShape m_Shape;
public:
    RectangleHitBox(const sf::FloatRect& offset);
    sf::FloatRect GetGlobalBounds() const override;
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetRotation(sf::Angle angle) override;
    std::vector<sf::Vector2f> GetTransformedPoints() override;
    void RenderDebug(sf::RenderTarget& target) const override;
};
