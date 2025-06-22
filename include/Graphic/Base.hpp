#pragma once

#include "SFML/Graphics.hpp"

class ArielText : public sf::Text
{
public:
    ArielText();
};

class GraphicBase
{
public:
    virtual bool Render(sf::RenderTarget &) const = 0;
    virtual bool Update(const sf::Time &) = 0;
    virtual bool FixLagUpdate(const sf::Time &) = 0;
    virtual bool SetPosition(const sf::Vector2f &) = 0;
    virtual bool HandleInput(const sf::Event &) = 0;
    virtual sf::Vector2f GetSize() const = 0;
};