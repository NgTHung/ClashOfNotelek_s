#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Event/Event.hpp"
#include "Utility/IDGenerator.hpp"
class Engine;

class Collidable : public sf::Transformable, public sf::Drawable {
private:
    ID m_ID;
    sf::Vector2f m_Size;

protected:
    std::vector<sf::Vector2f> m_Vertices;

public:
    Collidable(const sf::Vector2f &size);

    virtual void SetPosition(const sf::Vector2f &position);

    virtual void SetScale(const sf::Vector2f &scale);

    virtual void SetRotation(float angle);

    virtual GlobalEventType GetCollisionEventType() const = 0;

    virtual std::vector<sf::Vector2f> GetTransformedPoints() const;

    virtual sf::FloatRect GetBoundingBox() const;

    virtual sf::Vector2f GetSize() const;

    virtual sf::Vector2f GetPosition() const;

    virtual sf::Transform GetTransform() const;

    virtual sf::Vector2f GetScale() const;

    virtual sf::Vector2f GetOrigin() const;

    virtual void SetOrigin(sf::Vector2f origin);

    int GetID() const;

    void DrawDebug(sf::RenderTarget &Renderer) const;
};

class CollisionSystem {
private:
    Engine &m_Engine;
    std::array<std::vector<Collidable *>, 16> m_CollisionLayers;

    static std::shared_ptr<BaseEvent> CollisionEventFactory(Collidable *A,
                                                            Collidable *B);

public:
    CollisionSystem(Engine &g_Engine);

    ~CollisionSystem();

    static std::vector<sf::Vector2f> GetAxes(const std::vector<sf::Vector2f> &Points);

    static sf::Vector2f Project(const std::vector<sf::Vector2f> &Points, const sf::Vector2f &Axis);

    static bool CheckSATCollision(const std::vector<sf::Vector2f> &PointsA, const std::vector<sf::Vector2f> &PointsB);

    void HandleCollisions() const;

    void HandleEnemyAttackLayer() const;

    void HandleMapEnityCollisions() const;

    void AddCollidable(Collidable *collidable, int layer);

    // void RemoveCollidable(const Collidable* &collidable, int layer);

    void RemoveCollidable(const int &CollidableID, int layer);

    bool IsFree(sf::Vector2f newPosition, Collidable &collidable, int layer) const;
};
