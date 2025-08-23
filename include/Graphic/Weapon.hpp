#pragma once
#include <SFML/Graphics.hpp>

#include "Base.hpp"
#include "Utility/Environment.hpp"

class Weapon : public GraphicBase
{
protected:
    sf::IntRect m_Rect;
    int m_Index = Environment::DefaultTextureIndex;
    bool m_Attacking = Environment::DefaultAttackingState;
    float m_Damage = Environment::DefaultAttackingDamage;
    int m_AttackID;

public:
    static int s_AttackCount;

    Weapon(const sf::IntRect &Rect = Environment::DefaultIntRect);

    virtual void SetDamage(const float &damage) = 0;

    virtual float GetDamage() const = 0;

    virtual std::vector<sf::Vector2f> GetHitBoxPoint() = 0;

    virtual void Attack() = 0;

    virtual bool IsAttacking() const = 0;

    int GetAttackID() const;
};

class Sword : public Weapon
{
private:
    Engine &m_Engine;
    sf::RectangleShape m_Shape;



public:
    Sword(Engine &g_Engine);

    ~Sword() override;

    void SetPosition(const sf::Vector2f &position) override;

    void SetDamage(const float &damage) override;

    float GetDamage() const override;

    void RotateToMouse();

    void SetRotation(float angle) override;

    void SetScale(const sf::Vector2f &Scale) override;

    void SetOrigin(sf::Vector2f origin) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void Attack() override;

    bool IsAttacking() const override;

    std::vector<sf::Vector2f> GetHitBoxPoint() override;

    GlobalEventType GetCollisionEventType() const override;

    sf::Vector2f GetSize() const override;

    bool Update(const sf::Time &) override;

    bool HandleInput(const sf::Event &) override;
};
