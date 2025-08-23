#include <memory>

#include "Engine/Engine.hpp"
#include "State/StartScreen.hpp"
#include "Utility/Logger.hpp"
#include "State/HomeScreen.hpp"
#include "Utility/Environment.hpp"

Engine::Engine() : m_CollisionSystem(std::make_unique<CollisionSystem>(*this)),
                   m_Window(sf::VideoMode(Environment::ScreenResolution), Environment::GameName),
                   m_View(Environment::DefaultView),
                   m_ShouldPop(false), m_ShouldExit(false), m_ShouldChangeState(false),
                   m_EventQueue(std::make_unique<EventQueue>()) {
    m_Window.setFramerateLimit(Environment::FrameLimit);
}

void Engine::ResetWindow() {
    m_Window.setPosition(sf::Vector2i(0, 0));
}


void Engine::SetView(const sf::View &view) {
    m_View = view;
    m_Window.setView(m_View);
}

void Engine::ShakeScreen() {
    m_ScreenShake.Start();
}

ScreenShake &Engine::GetScreenShake() {
    return m_ScreenShake;
}

void Engine::ResetView() {
    m_View.setCenter(sf::Vector2f(Environment::ScreenResolution.x / 2, Environment::ScreenResolution.y / 2));
    this->SetView(m_View);
}

Screen &Engine::GetCurrentState() const {
    return *this->m_States.back();
}

void Engine::Prepare() {
    PushState<StartScreen>(*this);
}

void Engine::PopState() {
    m_ShouldPop = true;
}

bool Engine::PushState(std::unique_ptr<Screen> state) {
    m_States.push_back(std::move(state));
    return true;
}

const sf::RenderWindow &Engine::GetWindow() const {
    return m_Window;
}

void Engine::CloseWindow() {
    m_Window.close();
}


bool Engine::HandleInput() {
    while (const std::optional Event = m_Window.pollEvent()) {
        bool isSuccess = GetCurrentState().HandleInput(Event);
        if (Event->is<sf::Event::Closed>()) {
            m_Window.close();
        }
        if (!isSuccess) {
            LOG_ERROR("State Error.");
            return false;
        }
    }
    return true;
}

bool Engine::TryPop() {
    if (m_ShouldPop) {
        m_ShouldPop = false;
        if (m_ShouldExit) {
            m_States.clear();
            return true;
        }
        m_States.back().reset();
        m_States.pop_back();
        if (m_ShouldChangeState) {
            m_ShouldChangeState = false;
            return this->PushState(std::move(m_ChangedState));
        }
        m_reset = false;
        if (dynamic_cast<HomeScreen *>(m_States.back().get())) {
            m_reset = true;
            EventDispatcher::GetInstance().UnRegisterAllListeners();
            m_CollisionSystem = std::make_unique<CollisionSystem>(*this);
            m_EventQueue = std::make_unique<EventQueue>();
            m_States.back() = std::make_unique<HomeScreen>(*this);
        }
    }
    return true;
}

void Engine::PostEvent(const std::shared_ptr<BaseEvent> &Event) {
    this->m_EventQueue->PushEvent(Event);
}

void Engine::ProcessEvents() {
    while (!m_EventQueue->IsEmpty()) {
        auto Event = m_EventQueue->PopEvent();
        if (!Event.has_value() || !Event.value())
            continue;

        EventDispatcher::GetInstance().Dispatch(Event.value());
    }
}

CollisionSystem &Engine::GetCollisionSystem() {
    return *(m_CollisionSystem);
}

void Engine::Run() {
    sf::Clock Timer;

    while (m_Window.isOpen() && !m_States.empty()) {
        Screen &State = this->GetCurrentState();
        sf::Time Elapsed = Timer.restart();
        HandleInput();
        m_CollisionSystem->HandleCollisions();
        ProcessEvents();
        State.Update(Elapsed);
        m_Window.clear();
        State.Render(m_Window);
        m_Window.display();
        TryPop();
    }
}
