#include "Graphic/Wall.hpp"

#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Utility/Enviroment.hpp"
#include "Utility/Logger.hpp"

Wall::Wall(Engine &g_engine, const sf::Vector2f &position, const sf::Vector2f &size): GraphicBase(size),
                                                                                      m_Engine(g_engine) {
        
    m_Size = size;
    m_Engine.GetCollisionSystem().AddCollidable(this, Enviroment::PlayerCollisionLayer);
    m_Shape.setSize(size);
    m_Shape.setPosition(position);
    Collidable::SetPosition(position);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setOutlineColor(sf::Color::White);
    m_Shape.setOutlineThickness(1.f);
    m_Vertices.push_back(sf::Vector2f(0, 0));
    m_Vertices.push_back(sf::Vector2f(size.x, 0));
    m_Vertices.push_back(sf::Vector2f(size.x, size.y));
    m_Vertices.push_back(sf::Vector2f(0, size.y));
}

GlobalEventType Wall::GetCollisionEventType() const {
    return GlobalEventType::WallCollision;
}

sf::Vector2f Wall::GetSize() const {
    return m_Size;
}

bool Wall::Update(const sf::Time &) {
    return true;
}

bool Wall::FixLagUpdate(const sf::Time &) {
    return true;
}

bool Wall::HandleInput(const sf::Event &) {
    return true;
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //states.transform *= getTransform();
    target.draw(m_Shape);
}
