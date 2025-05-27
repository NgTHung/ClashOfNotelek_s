#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "State/BaseState.hpp"
class Engine
{
public:
    Engine();
    void Prepare();
    void Run();

    void PopState();
    template <typename T, typename... Args>
    bool PushState(Args &&...args);
    bool PushState(std::unique_ptr<BaseState> state);
    template <typename T, typename... Args>
    bool ChangeState(Args &&...args);

    const sf::RenderWindow &GetWindow() const;
    BaseState &GetCurrentState() const;

private:
    bool HandleEvent();
    bool TryPop();

    sf::RenderWindow m_Window;
    std::vector<std::unique_ptr<BaseState>> m_States;
    bool m_ShouldPop;
    bool m_ShouldExit;
    bool m_ShouldChangeState;
    std::unique_ptr<BaseState> m_ChangedState;
};