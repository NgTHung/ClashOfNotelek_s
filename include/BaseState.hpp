#pragma once
#include <SFML/Graphics.hpp>
class BaseState
{
private:
public:
    virtual ~BaseState();
    virtual bool render(const sf::RenderTarget &renderer);
    virtual bool update(const sf::Time &dt);
    virtual bool handleEvent();
};