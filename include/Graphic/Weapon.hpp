#pragma once
#include<SFML/Graphics.hpp>
#include"Engine/Engine.hpp"

#include "Base.hpp"
#include "Utility/Enviroment.hpp"

class Weapon : public GraphicBase {
protected:
    sf::Texture m_Texture;
    sf::IntRect m_Rect;
    int m_Index = Enviroment::DefaultTextureIndex;
    bool m_Attacking = Enviroment::DefaultAttackingState;
    float m_Damage = Enviroment::DefaultAttackingDamage;
public:
    Weapon(sf::Texture Texture, const sf::IntRect &Rect = Enviroment::DefaultIntRect);

    void SetPosition(const sf::Vector2f &position) override = 0;

    void SetScale(const sf::Vector2f &Scale) override = 0;

    virtual void RotateToMouse(const Engine &engine) = 0;

    virtual void SetDamage(const float &damage) = 0;

    virtual float GetDamage() const = 0;

    virtual void SetOrigin(const sf::Vector2f &Origin) = 0;

    virtual sf::VertexArray GetHitBoxPoint() = 0;

    virtual void Attack() = 0;

    virtual bool IsAttacking() const = 0;
};

class Sword : public Weapon {
private:
    const Engine &m_Engine;
public:
    Sword(Engine &g_Engine);

    void SetPosition(const sf::Vector2f &position) override;

    void SetDamage(const float &damage) override;

    float GetDamage() const override;

    void RotateToMouse(const Engine &engine) override;

    void SetRotation(const float angle) override;

    void SetScale(const sf::Vector2f &Scale) override;

    void SetOrigin(const sf::Vector2f &Origin) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void Attack() override;

    bool IsAttacking() const override;

    sf::VertexArray GetHitBoxPoint() override;

    GlobalEventType GetCollisionEventType() const override;

    sf::Vector2f GetSize() const override;

    bool Update(const sf::Time &) override;

    bool FixLagUpdate(const sf::Time &) override;

    bool HandleInput(const sf::Event &) override;
};
