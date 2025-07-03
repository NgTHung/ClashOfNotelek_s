#pragma once
#include<SFML/Graphics.hpp>
#include"Engine/Engine.hpp"
#include"Graphic/HitBox.hpp"
#include"Resources/ResourcesManager.hpp"
#include<vector>
#include <cmath>
#include"Utility/Logger.hpp"
class Weapon{
public:
    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual void SetRotation(const sf::Angle& angle) = 0 ;
    virtual void SetScale(const sf::Vector2f& Scale) = 0;
    virtual void RotateToMouse(const Engine& engine) = 0;
    virtual void SetDamage(const float& damage) = 0;
    virtual float GetDamge() const = 0;
    virtual void SetOrigin(const sf::Vector2f& Origin) = 0;
    virtual std::vector<sf::Vector2f> GetHitBoxPoint() = 0;
    virtual void Attack() = 0;
    virtual void Render(sf::RenderTarget& Renderer) = 0;
    virtual bool IsAttacking() const = 0;
};

class Sword: public Weapon{
private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    sf::IntRect m_Rect;
    std::unique_ptr<HitBox> m_HitBox;
    int m_Index;
    bool m_Attacking;
    float m_Damage;
public:
    Sword();
    void SetPosition(const sf::Vector2f& position) override;
    void SetDamage(const float& damage) override;
    float GetDamge() const override;
    void RotateToMouse(const Engine& engine) override;
    void SetRotation(const sf::Angle& angle) override;
    void SetScale(const sf::Vector2f& Scale) override; 
    void SetOrigin(const sf::Vector2f& Origin) override;
    void Render(sf::RenderTarget& Renderer) override;
    void Attack() override;
    bool IsAttacking() const override;
    std::vector<sf::Vector2f> GetHitBoxPoint() override;
};
