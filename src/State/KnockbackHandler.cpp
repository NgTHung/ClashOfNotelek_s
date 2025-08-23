#include "State/KnockbackHandler.hpp"
#include <cmath>

KnockBackHandler::KnockBackHandler()
    : m_Velocity(0.f, 0.f), m_Damping(600.f), m_Active(false) {}

void KnockBackHandler::ApplyVelocity(const sf::Vector2f& direction, float strength) {

    sf::Vector2f dir = direction;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.f) dir /= len;

    m_Velocity = dir * strength;
    m_Active = true;
}

void KnockBackHandler::Update(sf::Vector2f& position, float dt) {
    if (!m_Active) return;

    position += m_Velocity * dt;

    float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
    if (speed > 0.f) {
        float decel = m_Damping * dt;
        if (decel >= speed)
        {
            m_Velocity = {0.f, 0.f};
            m_Active = false;
        }
        else
        {
            m_Velocity -= m_Velocity / speed * decel;
        }
    }
}

bool KnockBackHandler::IsActive() const {
    return m_Active;
}

void KnockBackHandler::Stop() {
    m_Velocity = {0.f, 0.f};
    m_Active = false;
}