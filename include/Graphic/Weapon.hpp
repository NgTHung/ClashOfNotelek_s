#pragma once
#include <SFML/Graphics.hpp>

#include "Base.hpp"
#include "Utility/Enviroment.hpp"

class Weapon : public GraphicBase
{
protected:
    sf::IntRect m_Rect;
    int m_Index = Enviroment::DefaultTextureIndex;
    bool m_Attacking = Enviroment::DefaultAttackingState;
    float m_Damage = Enviroment::DefaultAttackingDamage;

public:
    Weapon(const sf::IntRect &Rect = Enviroment::DefaultIntRect);

    void SetPosition(const sf::Vector2f &position) override = 0;

    void SetScale(const sf::Vector2f &Scale) override = 0;

    virtual void SetDamage(const float &damage) = 0;

    virtual float GetDamage() const = 0;

    virtual void SetOrigin(const sf::Vector2f &Origin) = 0;

    virtual std::vector<sf::Vector2f> GetHitBoxPoint() = 0;

    virtual void Attack() = 0;

    virtual bool IsAttacking() const = 0;
};

class Sword : public Weapon
{
private:
    Engine &m_Engine;
    sf::RectangleShape m_Shape;
public:
    Sword(Engine &g_Engine);

    ~Sword();

    void SetPosition(const sf::Vector2f &position) override;

    void SetDamage(const float &damage) override;

    float GetDamage() const override;

    void RotateToMouse();

    void SetRotation(const float angle) override;

    void SetScale(const sf::Vector2f &Scale) override;

    void SetOrigin(const sf::Vector2f &Origin) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void Attack() override;

    bool IsAttacking() const override;

    std::vector<sf::Vector2f> GetHitBoxPoint() override;

    GlobalEventType GetCollisionEventType() const override;

    sf::Vector2f GetSize() const override;

    bool Update(const sf::Time &) override;

    bool FixLagUpdate(const sf::Time &) override;

    bool HandleInput(const sf::Event &) override;
};
