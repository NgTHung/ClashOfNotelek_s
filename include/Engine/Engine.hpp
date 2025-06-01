#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "State/ScreenState.hpp"

class Engine
{
public:
    Engine();
    void Prepare();
    void Run();

    void PopState();
    template <typename T, typename... Args>
    bool PushState(Args &&...args);
    bool PushState(std::unique_ptr<ScreenState> state);
    template <typename T, typename... Args>
    bool ChangeState(Args &&...args);

    const sf::RenderWindow &GetWindow() const;
    ScreenState &GetCurrentState() const;

private:
    bool HandleInput();
    bool TryPop();

    sf::RenderWindow m_Window;
    std::vector<std::unique_ptr<ScreenState>> m_States;
    bool m_ShouldPop;
    bool m_ShouldExit;
    bool m_ShouldChangeState;
    std::unique_ptr<ScreenState> m_ChangedState;
};