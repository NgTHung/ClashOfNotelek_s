#pragma once
#include <SFML/Graphics.hpp>
#include "Event/EventQueue.hpp"
#include "Command/Command.hpp"
class Engine;

class ScreenState
{
protected:
    std::shared_ptr<Engine> m_Engine;
    EventQueue m_EventQueue;

public:
    virtual ~ScreenState() = default;
    virtual bool Render(sf::RenderTarget &Renderer) = 0;
    virtual bool Update(const sf::Time &DT) = 0;
    virtual bool HandleEvent() = 0;
    virtual bool HandleInput(const std::optional<sf::Event> Event) = 0;
    virtual bool FixLagUpdate(const sf::Time &DT) = 0;
};