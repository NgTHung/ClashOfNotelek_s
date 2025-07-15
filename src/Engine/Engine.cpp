#include "Engine/Engine.hpp"
#include "State/StartScreen.hpp"
#include "Utility/Logger.hpp"
#include "State/HomeScreen.hpp"
#include "Utility/Enviroment.hpp"

Engine::Engine() : m_Window(sf::VideoMode(Enviroment::ScreenResolution), Enviroment::GameName), m_ShouldPop(false), m_ShouldExit(false),
                   m_ShouldChangeState(false), m_CollisionSystem(*this)
{
    m_Window.setFramerateLimit(Enviroment::FrameLimit);
}

Screen &Engine::GetCurrentState() const
{
    return *this->m_States.back();
}

void Engine::Prepare()
{

    PushState<StartScreen>(*this);
}

void Engine::PopState()
{
    m_ShouldPop = true;
}

bool Engine::PushState(std::unique_ptr<Screen> state)
{
    m_States.push_back(std::move(state));
    return true;
}

const sf::RenderWindow &Engine::GetWindow() const
{
    return m_Window;
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
            return this->PushState(std::move(m_ChangedState));
        }

        m_States.back().reset();
        m_States.pop_back();
    }
    return true;
}

void Engine::PostEvent(const std::shared_ptr<BaseEvent> &Event)
{
    this->m_EventQueue.PushEvent(Event);
}

void Engine::ProcessEvents()
{
    while (!m_EventQueue.IsEmpty())
    {
        auto Event = m_EventQueue.PopEvent();
        if (!Event.has_value() || !Event.value())
            continue;

        EventDispatcher::GetInstance().Dispatch(Event.value());
    }
}

CollisionSystem & Engine::GetCollisionSystem() {
    return m_CollisionSystem;   
}

void Engine::Run()
{
    int Ticks = 0;

    sf::Clock Timer;
    sf::Time LastTime = sf::Time::Zero;
    sf::Time Lag = sf::Time::Zero;

    LOG_DEBUG("TPU: {}", Enviroment::TimePerUpdate.asSeconds());

    while (m_Window.isOpen() && !m_States.empty())
    {
        Screen &State = this->GetCurrentState();

        sf::Time Time = Timer.getElapsedTime();
        sf::Time Elapsed = Time - LastTime;

        LOG_DEBUG("Elapsed: {}", Elapsed.asSeconds());

        LastTime = Time;
        Lag += Elapsed;
        HandleInput();
        m_CollisionSystem.HandleCollisions();
        ProcessEvents();
        State.Update(Elapsed);

        while (Lag >= Enviroment::TimePerUpdate)
        {
            Ticks++;
            Lag -= Enviroment::TimePerUpdate;
            State.FixLagUpdate(Elapsed);
        }

        m_Window.clear();
        State.Render(m_Window);
        m_Window.display();

        TryPop();
    }
}
