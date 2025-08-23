#pragma once
#include <SFML/Graphics.hpp>

class KnockBackHandler
{
private:
    sf::Vector2f m_Velocity;
    float m_Damping;
    bool m_Active;
public:
    KnockBackHandler();

    void ApplyVelocity(const sf::Vector2f& direction, float strength);

    void Update(sf::Vector2f& position, float deltaTime);

    bool IsActive() const;
    void Stop();
};