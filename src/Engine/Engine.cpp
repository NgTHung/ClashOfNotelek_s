#include "Engine/Engine.hpp"
#include "State/StartState.hpp"
#include "Utility/Logger.hpp"

Engine::Engine() : m_Window(sf::VideoMode({1280, 720}), "Clash of Notelek\'s"), m_ShouldPop(false), m_ShouldExit(false),
                   m_ShouldChangeState(false)
{
    m_Window.setFramerateLimit(60);
}

ScreenState &Engine::GetCurrentState() const
{
    return *this->m_States.back();
}

void Engine::Prepare()
{
    PushState<StartState>(this->m_Window);
}

void Engine::PopState()
{
    m_ShouldPop = true;
}

bool Engine::PushState(std::unique_ptr<ScreenState> state)
{
    m_States.push_back(std::move(state));
    return true;
}

const sf::RenderWindow &Engine::GetWindow() const
{
    return m_Window;
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

bool Engine::HandleInput()
{
    while (const std::optional Event = m_Window.pollEvent())
    {
        bool isSuccess = GetCurrentState().HandleInput(Event);
        if (Event->is<sf::Event::Closed>())
        {
            m_Window.close();
        }
        if (!isSuccess)
        {
            LOG_ERROR("State Error.");
            return false;
        }
    }
    return true;
}

bool Engine::TryPop()
{
    if (m_ShouldPop)
    {
        m_ShouldPop = false;
        if (m_ShouldExit)
        {
            m_States.clear();
            return true;
        }
        else if (m_ShouldChangeState)
        {
            m_ShouldChangeState = false;
            m_States.back().reset();
            m_States.pop_back();
            this->PushState(std::move(m_ChangedState));
            return true;
        }

        m_States.back().reset();
        m_States.pop_back();
    }
    return true;
}

void Engine::Run()
{
    constexpr int TPS = 30; // Tick Per Second
    constexpr sf::Time TimePerUpdate = sf::seconds(1.f / TPS);
    int Ticks = 0;

    sf::Time LastTime = sf::Time::Zero;
    sf::Time Lag = sf::Time::Zero;

    while (m_Window.isOpen() && !m_States.empty())
    {
        sf::Clock Timer;
        ScreenState &State = this->GetCurrentState();

        sf::Time Time = Timer.getElapsedTime();
        sf::Time Elapsed = Time - LastTime;
        LastTime = Time;
        Lag += Elapsed;

        HandleInput();
        State.Update(Elapsed);

        while (Lag >= TimePerUpdate)
        {
            Ticks++;
            Lag -= TimePerUpdate;
            State.FixLagUpdate(Elapsed);
        }

        m_Window.clear();
        State.Render(m_Window);
        m_Window.display();

        State.HandleEvent();
        TryPop();
    }
}