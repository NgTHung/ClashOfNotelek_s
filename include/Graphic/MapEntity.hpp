#pragma once
#include "Wall.hpp"
#include "Graphic/Base.hpp"
#include "SFML/Audio/Listener.hpp"

class Tree: public GraphicBase
{
private:
    Engine& m_Engine;
    sf::Sprite m_SpriteTree;
public:
    Tree(Engine& g_Engine,const sf::Vector2f& size);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetOrigin(sf::Vector2f origin) override;
    bool Update(const sf::Time& ) override;
    bool FixLagUpdate(const sf::Time& ) override;
    bool HandleInput(const sf::Event& ) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    float GetYAxisPoint() override;
};

class Grass: public GraphicBase
{
private:
    Engine& m_Engine;
    sf::Sprite m_Sprite;
    int m_Index = 0;
    int m_MilliSecondUpdate = 0;
public:
    Grass(Engine& g_Engine,const sf::Vector2f& size);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetOrigin(sf::Vector2f origin) override;
    bool Update(const sf::Time& ) override;
    bool FixLagUpdate(const sf::Time& ) override;
    bool HandleInput(const sf::Event& ) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    float GetYAxisPoint() override;
};

class TinyGrass: public GraphicBase
{
private:
    Engine& m_Engine;
    sf::Sprite m_Sprite;
    int m_Index = 0;
    int m_MilliSecondUpdate = 0;
public:
    TinyGrass(Engine& g_Engine,const sf::Vector2f& size);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetOrigin(sf::Vector2f origin) override;
    bool Update(const sf::Time& ) override;
    bool FixLagUpdate(const sf::Time& ) override;
    bool HandleInput(const sf::Event& ) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    float GetYAxisPoint() override;
};

class Box: public GraphicBase
{
private:
    Engine& m_Engine;
    sf::Sprite m_Sprite;

public:
    Box(Engine& g_Engine,const sf::Vector2f& size);
    void SetPosition(const sf::Vector2f& position) override;
    void SetScale(const sf::Vector2f& scale) override;
    void SetOrigin(sf::Vector2f origin) override;
    bool Update(const sf::Time& ) override;
    bool FixLagUpdate(const sf::Time& ) override;
    bool HandleInput(const sf::Event& ) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    float GetYAxisPoint() override;
};