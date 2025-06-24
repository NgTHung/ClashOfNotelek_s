#pragma once
#include <SFML/Graphics.hpp>
#include <numbers>
#include <cmath>
class HitBox
{   
public:
    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual void RenderDebug(sf::RenderTarget& target) const = 0;
    virtual void SetScale(const sf::Vector2f& scale) = 0;
    virtual void SetRotation(sf::Angle angle) = 0;
    virtual std::vector<sf::Vector2f> GetTransformedPoints() const = 0;
    virtual ~HitBox() = default;
};

class RectangleHitBox : public HitBox
{
private:
    sf::FloatRect m_Offset;
    sf::RectangleShape m_Shape;
public:
    RectangleHitBox(const sf::FloatRect& offset);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetRotation(sf::Angle angle) override;
    std::vector<sf::Vector2f> GetTransformedPoints() const override;
    void RenderDebug(sf::RenderTarget& target) const override;
};

class QuarterCircleHitBox: public HitBox
{
private:
    sf::Vector2f m_Center;
    float m_Radius;
    sf::Angle m_Rotation;
    sf::Vector2f m_Scale;
    int m_Segment;

public:
    QuarterCircleHitBox(const float& Radius,const sf::Vector2f& Center);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    sf::Angle GetRotation() const;
    void SetRotation(sf::Angle angle) override;
    std::vector<sf::Vector2f> GetTransformedPoints() const override;
    void RenderDebug(sf::RenderTarget& target) const override;
};
