#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Base.hpp"

class Leaf: public  GraphicBase
{
private:
    sf::Sprite m_Sprite;
    float m_FallSpeed;
    float m_SwingSpeed;
    float m_SwingAmount;
    float m_RotationSpeed;
    float m_Time;
    float m_StartX;
public:
    Leaf(const sf::Texture& tex,const sf::Vector2f& spawnPos,const float& fallSpeed,const float& swingSpeed,const float& swingAmount,const float& rotationSpeed);
    ~Leaf() override = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    sf::Vector2f GetPosition() const override;
    bool Update(const sf::Time&) override;
    bool HandleInput(const sf::Event&) override;
};



class LeafFalling: public GraphicBase
{
public:
    LeafFalling(Engine& g_Engine,const sf::FloatRect& spawnArea,const int& leafCount);
    ~LeafFalling() override = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    bool HandleInput(const sf::Event&) override;

private:
    sf::FloatRect m_spawnArea;
    Engine& m_Engine;
    void SpawnLeave();
    std::vector<const sf::Texture*> m_Textures;
    std::vector<std::shared_ptr<Leaf>> m_Leaves;
};
