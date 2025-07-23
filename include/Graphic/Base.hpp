    #pragma once

#include "Collision.hpp"
#include "SFML/Graphics.hpp"

class ArielText : public sf::Text
{
public:
    ArielText();
};

class GraphicBase: public Collidable
{
public:
    GraphicBase(const sf::Vector2f &size);
    virtual bool Update(const sf::Time &) = 0;
    virtual bool FixLagUpdate(const sf::Time &) = 0;
    virtual bool HandleInput(const sf::Event &) = 0;
};