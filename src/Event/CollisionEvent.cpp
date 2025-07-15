#include "Event/CollisionEvent.hpp"

#include "Utility/Logger.hpp"

CollisionEvent::CollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B):
    m_CollidableA(A), m_CollidableB(B) {
    if (!m_CollidableA || !m_CollidableB) {
        LOG_ERROR("CollidableA or CollidableB is null in CollisionEvent");
        throw std::invalid_argument("CollidableA or CollidableB cannot be null");
    }
}

GlobalEventType CollisionEvent::GetEventType() const {
    return GlobalEventType::Collision;
}

std::shared_ptr<Collidable> CollisionEvent::GetCollidableA() const {
    return m_CollidableA;
}

std::shared_ptr<Collidable> CollisionEvent::GetCollidableB() const {
    return m_CollidableB;
}

GlobalEventType PlayerCollisionEvent::GetEventType() const {
    return GlobalEventType::CharacterCollision;
}

PlayerCollisionEvent::PlayerCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B): CollisionEvent(A,B) {
}
WallCollisionEvent::WallCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B): CollisionEvent(A,B) {
}
EnemyCollisionEvent::EnemyCollisionEvent(const std::shared_ptr<Collidable> &A, const std::shared_ptr<Collidable> &B): CollisionEvent(A,B) {
}

GlobalEventType WallCollisionEvent::GetEventType() const {
    return GlobalEventType::WallCollision;
}

GlobalEventType EnemyCollisionEvent::GetEventType() const {
    return GlobalEventType::EnemyCollision;
}
