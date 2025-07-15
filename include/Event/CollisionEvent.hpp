#pragma once
#include <memory>

#include "Event/Event.hpp"

class Collidable;

class CollisionEvent : public BaseEvent {
private:
    std::shared_ptr<Collidable> m_CollidableA;
    std::shared_ptr<Collidable> m_CollidableB;

public:
    CollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B);
    GlobalEventType GetEventType() const override;
    std::shared_ptr<Collidable> GetCollidableA() const;
    std::shared_ptr<Collidable> GetCollidableB() const;
};

class PlayerCollisionEvent : public CollisionEvent {
private:
    std::shared_ptr<Collidable> m_CollidableA;
    std::shared_ptr<Collidable> m_CollidableB;

public:
    GlobalEventType GetEventType() const override;
    PlayerCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B);
};

class WallCollisionEvent : public CollisionEvent {
private:
    std::shared_ptr<Collidable> m_CollidableA;
    std::shared_ptr<Collidable> m_CollidableB;

public:
    WallCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B);
    GlobalEventType GetEventType() const override;
};

class EnemyCollisionEvent : public CollisionEvent {
private:
    std::shared_ptr<Collidable> m_CollidableA;
    std::shared_ptr<Collidable> m_CollidableB;

public:
    EnemyCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B);
    GlobalEventType GetEventType() const override;
};
