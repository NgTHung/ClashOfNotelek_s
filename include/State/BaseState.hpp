#pragma once
#include <SFML/Graphics.hpp>
class BaseState
{
private:
public:
    virtual ~BaseState() = default;
    virtual bool Render(sf::RenderTarget &Renderer) const = 0;
    virtual bool Update(const sf::Time &DT) = 0;
    virtual bool HandleEvent(const std::optional<sf::Event> Event) = 0;
    virtual bool HandleInput() = 0;
    virtual bool FixLagUpdate(const sf::Time &DT) = 0;
};