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
    sf::VertexArray m_vertices;

public:
    Collidable(const sf::Vector2f &size);

    virtual void SetPosition(const sf::Vector2f &position);

    virtual void SetScale(const sf::Vector2f &scale) ;

    virtual void SetRotation(float angle);

    virtual GlobalEventType GetCollisionEventType() const = 0;

    virtual sf::VertexArray GetTransformedPoints() const;

    virtual sf::FloatRect GetBoundingBox() const;

    virtual sf::Vector2f GetSize() const;

    virtual sf::Vector2f GetPosition() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    int GetID() const;;
};

class CollisionSystem {
private:
    Engine &m_Engine;
    std::array<std::vector<std::shared_ptr<Collidable> >, 16> m_CollisionLayers;

    static std::shared_ptr<BaseEvent> CollisionEventFactory(const std::shared_ptr<Collidable> &A,
                                                            const std::shared_ptr<Collidable> &B);

public:
    CollisionSystem(Engine &g_Engine);

    static std::vector<sf::Vector2f> GetAxes(const sf::VertexArray &Points);

    static sf::Vector2f Project(const sf::VertexArray &Points, const sf::Vector2f &Axis);

    static bool CheckSATCollision(const sf::VertexArray &PointsA, const sf::VertexArray &PointsB);

    void HandleCollisions() const;

    void AddCollidable(const std::shared_ptr<Collidable> &collidable, int layer);

    void RemoveCollidable(const std::shared_ptr<Collidable> &collidable, int layer);

    bool IsFree(sf::Vector2f newPosition, const std::shared_ptr<Collidable*>& collidable, int layer) const;
};
