#include "Graphic/Wall.hpp"

#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Event/EventDispatcher.hpp"
#include "Utility/Enviroment.hpp"

Wall::Wall(Engine& g_engine, const sf::Vector2f &position, const sf::Vector2f &size): m_Engine(g_engine), GraphicBase(size) {
    setPosition(position);
    m_Size = size;
    m_Engine.GetCollisionSystem().AddCollidable(std::shared_ptr<Collidable>(this), Enviroment::PlayerCollisionLayer);
}

void Wall::SetPosition(const sf::Vector2f &position) {
    setPosition(position);
}

void Wall::SetScale(const sf::Vector2f &scale) {
    setScale(scale);
}

void Wall::SetRotation(float angle) {
    setRotation(sf::degrees(angle));
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
    GraphicBase::draw(target, states);
}
