#include"Graphic/Collision.hpp"

#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Utility/Logger.hpp"
#include <cmath>

Collidable::Collidable(const sf::Vector2f &size): m_Size(size) {
}

void Collidable::SetPosition(const sf::Vector2f &position) {
    setPosition(position);
}

void Collidable::SetScale(const sf::Vector2f &scale) {
    setScale(scale);
}

void Collidable::SetRotation(float angle) {
    setRotation(sf::degrees(angle));
}

sf::Vector2f Collidable::GetSize() const {
    return m_Size;
}

sf::Vector2f Collidable::GetPosition() const {
    return getPosition();
}

sf::VertexArray Collidable::GetTransformedPoints() const {
    return this->m_vertices;
}

sf::FloatRect Collidable::GetBoundingBox() const {
    return sf::FloatRect(
        getPosition(),
        GetSize()
    );
}

void Collidable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_vertices, states);
}

int Collidable::GetID() const {
    return m_ID.GetID();
}

std::shared_ptr<BaseEvent> CollisionSystem::CollisionEventFactory(const std::shared_ptr<Collidable> &A,
                                                                  const std::shared_ptr<Collidable> &B) {
    if (A->GetCollisionEventType() == GlobalEventType::CharacterCollision) {
        return std::make_shared<PlayerCollisionEvent>(A, B);
    }
    if (A->GetCollisionEventType() == GlobalEventType::WallCollision) {
        return std::make_shared<WallCollisionEvent>(A, B);
    }
    if (A->GetCollisionEventType() == GlobalEventType::EnemyCollision) {
        return std::make_shared<EnemyCollisionEvent>(A, B);
    }
    LOG_ERROR("Unknown collision event type for collidable with ID: {}", A->GetID());
    return nullptr;
}

CollisionSystem::CollisionSystem(Engine &g_Engine): m_Engine(g_Engine) {
}

void CollisionSystem::HandleCollisions() const {
    for (const auto &Layer: m_CollisionLayers) {
        for (size_t i = 0; i < Layer.size(); ++i) {
            for (size_t j = i + 1; j < Layer.size(); ++j) {
                const auto &A = Layer[i];
                const auto &B = Layer[j];
                if (CheckSATCollision(A->GetTransformedPoints(), B->GetTransformedPoints())) {
                    m_Engine.PostEvent(CollisionEventFactory(A, B));
                    m_Engine.PostEvent(CollisionEventFactory(B, A));
                }
            }
        }
    }
}

void CollisionSystem::AddCollidable(const std::shared_ptr<Collidable> &collidable, const int layer) {
    this->m_CollisionLayers[layer].push_back(collidable);
}

void CollisionSystem::RemoveCollidable(const std::shared_ptr<Collidable> &collidable, const int layer) {
    for (auto it = m_CollisionLayers[layer].begin(); it != m_CollisionLayers[layer].end(); ++it) {
        if (it->get()->GetID() == collidable->GetID()) {
            m_CollisionLayers[layer].erase(it);
            return;
        }
    }
}

bool CollisionSystem::IsFree(sf::Vector2f newPosition, const std::shared_ptr<Collidable*> &collidable, const int layer) const {
    sf::Vector2f OldPosition = (*collidable.get())->getPosition();
   (*collidable.get())->setPosition(newPosition);
    for (auto &OtherCollidable: m_CollisionLayers[layer]) {
        if (OtherCollidable->GetID() ==(*collidable.get())->GetID()) {
            continue;
        }
        if (CheckSATCollision((*collidable.get())->GetTransformedPoints(), OtherCollidable->GetTransformedPoints())) {
           (*collidable.get())->setPosition(OldPosition);
            return false;
        }
    }
    (*collidable.get())->setPosition(OldPosition);
    return true;
}

std::vector<sf::Vector2f> CollisionSystem::GetAxes(const sf::VertexArray &Points) {
    std::vector<sf::Vector2f> Axes;
    for (int i = 0; i < Points.getVertexCount(); i++) {
        int NextIndex = (i + 1) % Points.getVertexCount();
        sf::Vector2f Vertices = Points[NextIndex].position - Points[i].position;
        sf::Vector2f Normal(-Vertices.y, Vertices.x);
        float Length = sqrt(Normal.x * Normal.x + Normal.y * Normal.y);
        if (Length != 0.0f) Normal /= Length;
        Axes.push_back(Normal);
    }
    return Axes;
}

sf::Vector2f CollisionSystem::Project(const sf::VertexArray &Points, const sf::Vector2f &Axis) {
    sf::Vector2f res = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    for (int i = 0; i < Points.getVertexCount(); i++) {
        float Projection = Points[i].position.x * Axis.x + Points[i].position.y * Axis.y;
        if (Projection < res.x)
            res.x = Projection;
        if (Projection > res.y)
            res.y = Projection;
    }
    return res;
}

bool CollisionSystem::CheckSATCollision(const sf::VertexArray &PointsA,
                                        const sf::VertexArray &PointsB) {
    std::vector<sf::Vector2f> AxesA = GetAxes(PointsA);
    std::vector<sf::Vector2f> AxesB = GetAxes(PointsB);
    for (sf::Vector2f &Axis: AxesA) {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if (ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false;
    }
    for (sf::Vector2f &Axis: AxesB) {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if (ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false;
    }
    return true;
}
