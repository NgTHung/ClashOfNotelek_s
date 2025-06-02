#pragma once
#include <SFML/Graphics.hpp>
#include "Event/EventQueue.hpp"
class Engine;

class Screen
{
protected:
    Engine &m_Engine;

public:
    Screen(Engine &g_Engine) : m_Engine(g_Engine) {};
    virtual ~Screen() = default;
    virtual bool Render(sf::RenderTarget &Renderer) = 0;
    virtual bool Update(const sf::Time &DT) = 0;
    virtual bool HandleEvent(std::shared_ptr<BaseEvent> Event) = 0;
    virtual bool HandleInput(const std::optional<sf::Event> Event) = 0;
    virtual bool FixLagUpdate(const sf::Time &DT) = 0;
};