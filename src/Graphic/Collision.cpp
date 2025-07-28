#include "Graphic/Collision.hpp"

#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Utility/Logger.hpp"
#include <cmath>

Collidable::Collidable(const sf::Vector2f &size) : m_Size(size)
{
}

void Collidable::SetPosition(const sf::Vector2f &position)
{
    setPosition(position);
}

void Collidable::SetScale(const sf::Vector2f &scale)
{
    setScale(scale);
}

void Collidable::SetRotation(float angle)
{
    setRotation(sf::degrees(angle));
}

sf::Vector2f Collidable::GetSize() const
{
    return m_Size;
}

sf::Vector2f Collidable::GetPosition() const
{
    return getPosition();
}

sf::Transform Collidable::GetTransform() const {
    return getTransform();
}

sf::Vector2f Collidable::GetScale() const
{
    return getScale();
}

sf::Vector2f Collidable::GetOrigin() const {
    return getOrigin();
}

void Collidable::SetOrigin(sf::Vector2f origin) {
    setOrigin(origin);
}

std::vector<sf::Vector2f> Collidable::GetTransformedPoints() const
{
    auto transform = getTransform();
    std::vector<sf::Vector2f> transformedPoints;
    for (const auto &vertex : m_Vertices)
    {
        transformedPoints.push_back(transform.transformPoint(vertex));
    }
    return transformedPoints;
}

sf::FloatRect Collidable::GetBoundingBox() const
{
    return sf::FloatRect(
        getPosition(),
        GetSize());
}

int Collidable::GetID() const
{
    return m_ID.GetID();
}

void Collidable::DrawDebug(sf::RenderTarget& Renderer) const {
    std::vector<sf::Vector2f> Points;
    Points = this->GetTransformedPoints();
    sf::VertexArray shape(sf::PrimitiveType::LineStrip,Points.size() + 1);
    for (size_t i = 0; i < Points.size(); ++i) {
        shape[i].position = Points[i];
        shape[i].color = sf::Color::Red;
    }
    if(Points.size() > 0)
        shape[Points.size()].position = Points[0];
    shape[Points.size()].color = sf::Color::Red;
    Renderer.draw(shape);
}

std::shared_ptr<BaseEvent> CollisionSystem::CollisionEventFactory(Collidable *A,
                                                                  Collidable *B)
{
    if (A->GetCollisionEventType() == GlobalEventType::CharacterCollision)
    {
        return std::make_shared<PlayerCollisionEvent>(A, B);
    }
    if (A->GetCollisionEventType() == GlobalEventType::WallCollision)
    {
        return std::make_shared<WallCollisionEvent>(A, B);
    }
    if (A->GetCollisionEventType() == GlobalEventType::EnemyCollision)
    {
        return std::make_shared<EnemyCollisionEvent>(A, B);
    }
    if (A->GetCollisionEventType() == GlobalEventType::SwordCollision)
    {
        return std::make_shared<SwordCollisionEvent>(A, B);
    }
    LOG_ERROR("Unknown collision event type for collidable with ID: {}", A->GetID());
    return nullptr;
}



CollisionSystem::CollisionSystem(Engine &g_Engine) : m_Engine(g_Engine)
{
}

CollisionSystem::~CollisionSystem()
{
    for (int Layer = 0; Layer < 16; Layer++)
    {
        m_CollisionLayers[Layer].clear();
    }
}

void CollisionSystem::HandleCollisions() const
{
    for (const auto &Layer : m_CollisionLayers)
    {
        for (size_t i = 0; i < Layer.size(); ++i)
        {
            for (size_t j = i + 1; j < Layer.size(); ++j)
            {
                const auto &A = Layer[i];
                const auto &B = Layer[j];
                if (CheckSATCollision(A->GetTransformedPoints(), B->GetTransformedPoints()))
                {
                    m_Engine.PostEvent(CollisionEventFactory(A, B));
                    m_Engine.PostEvent(CollisionEventFactory(B, A));
                }
            }
        }
    }
}

void CollisionSystem::AddCollidable(Collidable *collidable, const int layer)
{
    this->m_CollisionLayers[layer].push_back(collidable);
}

void CollisionSystem::RemoveCollidable(const int &ID, int layer)
{
    for (auto it = m_CollisionLayers[layer].begin(); it != m_CollisionLayers[layer].end(); ++it)
    {
        if ((*it)->GetID() == ID)
        {
            m_CollisionLayers[layer].erase(it);
            return;
        }
    }
}

bool CollisionSystem::IsFree(sf::Vector2f newPosition, Collidable &collidable, const int layer) const
{
    sf::Vector2f OldPosition = collidable.GetPosition();
    collidable.SetPosition(newPosition);
    for (auto &OtherCollidable : m_CollisionLayers[layer])
    {
        if (OtherCollidable->GetID() == collidable.GetID())
        {
            continue;
        }
        if (CheckSATCollision(collidable.GetTransformedPoints(), OtherCollidable->GetTransformedPoints()))
        {
            collidable.SetPosition(OldPosition);
            return false;
        }
    }
    collidable.SetPosition(OldPosition);
    return true;
}

std::vector<sf::Vector2f> CollisionSystem::GetAxes(const std::vector<sf::Vector2f> &Points)
{
    std::vector<sf::Vector2f> Axes;
    for (int i = 0; i < Points.size(); i++)
    {
        int NextIndex = (i + 1) % Points.size();
        sf::Vector2f Vertices = Points[NextIndex] - Points[i];
        sf::Vector2f Normal(-Vertices.y, Vertices.x);
        float Length = sqrt(Normal.x * Normal.x + Normal.y * Normal.y);
        if (Length != 0.0f)
            Normal /= Length;
        Axes.push_back(Normal);
    }
    return Axes;
}

sf::Vector2f CollisionSystem::Project(const std::vector<sf::Vector2f> &Points, const sf::Vector2f &Axis)
{
    sf::Vector2f res = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    for (int i = 0; i < Points.size(); i++)
    {
        float Projection = Points[i].x * Axis.x + Points[i].y * Axis.y;
        if (Projection < res.x)
            res.x = Projection;
        if (Projection > res.y)
            res.y = Projection;
    }
    return res;
}

bool CollisionSystem::CheckSATCollision(const std::vector<sf::Vector2f> &PointsA,
                                        const std::vector<sf::Vector2f> &PointsB)
{
    std::vector<sf::Vector2f> AxesA = GetAxes(PointsA);
    std::vector<sf::Vector2f> AxesB = GetAxes(PointsB);
    for (sf::Vector2f &Axis : AxesA)
    {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if (ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false;
    }
    for (sf::Vector2f &Axis : AxesB)
    {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if (ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false;
    }
    return true;
}
