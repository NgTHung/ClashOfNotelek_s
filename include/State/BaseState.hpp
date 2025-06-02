#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Event/EventQueue.hpp"

template <class T>
class BaseState
{
protected:
    T &m_Instance;

public:
    BaseState(T &Instance): m_Instance(Instance) {};
    virtual ~BaseState() = default;
    virtual void EnterState() = 0;
    virtual void ExitState() = 0;
    virtual std::unique_ptr<BaseState> FixLagUpdate(const sf::Time &DT) = 0;
    virtual std::unique_ptr<BaseState> HandleInput(const std::optional<sf::Event> Event) = 0;
    virtual std::unique_ptr<BaseState> Update(const sf::Time &DT) = 0;
    virtual bool HandleEvent(std::shared_ptr<BaseEvent>) = 0;
};
