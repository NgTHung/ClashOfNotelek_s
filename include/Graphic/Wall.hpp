#pragma once

#include "Graphic/Base.hpp"

class Wall : public GraphicBase
{
private:
    sf::Vector2f m_Size;
    Engine &m_Engine;
    sf::RectangleShape m_Shape;
public:
    Wall(Engine& g_engine, const sf::Vector2f &position, const sf::Vector2f &size);

    GlobalEventType GetCollisionEventType() const override;

    sf::Vector2f GetSize() const override;

    bool Update(const sf::Time &) override;

    bool HandleInput(const sf::Event &) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


};