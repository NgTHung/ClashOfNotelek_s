#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Event/EventDispatcher.hpp"
#include "Graphic/Collision.hpp"
#include "State/Screen.hpp"
#include "Graphic/ScreenShake.hpp"

class Engine
{
public:
    Engine();
    void Prepare();
    void Run();

    void PopState();
    template <typename T, typename... Args>
    bool PushState(Args &&...args);
    bool PushState(std::unique_ptr<Screen> state);
    template <typename T, typename... Args>
    bool ChangeState(Args &&...args);

    void ResetWindow();
    void SetView(const sf::View& view);
    void ShakeScreen();
    ScreenShake& GetScreenShake();
    void ResetView();
    const sf::RenderWindow &GetWindow() const;
    void CloseWindow();
    Screen &GetCurrentState() const;
    void PostEvent(const std::shared_ptr<BaseEvent> &Event);
    template <typename T, typename... Args>
    void PostEvent(Args &&...args);
    void ProcessEvents();

    CollisionSystem &GetCollisionSystem();

private:
    bool HandleInput();
    bool TryPop();

    std::unique_ptr<CollisionSystem> m_CollisionSystem;
    ScreenShake m_ScreenShake;
    sf::RenderWindow m_Window;
    sf::View m_View;
    std::vector<std::unique_ptr<Screen>> m_States;
    bool m_ShouldPop;
    bool m_ShouldExit;
    bool m_ShouldChangeState;
    std::unique_ptr<Screen> m_ChangedState;
    std::unique_ptr<EventQueue> m_EventQueue;
    bool m_reset = false;
};

template <typename T, typename... Args>
void Engine::PostEvent(Args &&...args)
{
    this->m_EventQueue->PushEvent<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
bool Engine::PushState(Args &&...args)
{
    return PushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
bool Engine::ChangeState(Args &&...args)
{
    m_ChangedState = std::make_unique<T>(std::forward<Args>(args)...);
    m_ShouldPop = true;
    m_ShouldChangeState = true;
    return true;
}
