    #include "Engine/Engine.hpp"
    #include "State/StartScreen.hpp"
    #include "Utility/Logger.hpp"
    #include "State/HomeScreen.hpp"
    #include "Utility/Enviroment.hpp"

    Engine::Engine() : m_CollisionSystem(std::make_unique<CollisionSystem>(*this)), m_Window(sf::VideoMode(Enviroment::ScreenResolution), Enviroment::GameName), m_View(Enviroment::DefaultView),
                       m_ShouldPop(false), m_ShouldExit(false),m_ShouldChangeState(false), m_EventQueue(std::make_unique<EventQueue>())
    {
        m_Window.setFramerateLimit(Enviroment::FrameLimit);

    }

    void Engine::ResetWindow()
    {
        m_Window.setPosition(sf::Vector2i(0,0));
    }


    void Engine::SetView(const sf::View& view)
    {
        m_View = view;
        m_Window.setView(m_View);
    }

    void Engine::ShakeScreen()
    {
        m_ScreenShake.Start();
    }

    ScreenShake& Engine::GetScreenShake()
    {
        return m_ScreenShake;
    }

    void Engine::ResetView()
    {
        m_View.setCenter(sf::Vector2f(Enviroment::ScreenResolution.x / 2, Enviroment::ScreenResolution.y / 2));
       this->SetView(m_View);
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

    void Engine::CloseWindow()
    {
        m_Window.close();
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
            m_reset = false;
            if (dynamic_cast<HomeScreen*>(m_States.back().get()))
            {
                m_reset = true;
                EventDispatcher::GetInstance().UnRegisterAllListeners();
                m_CollisionSystem.reset(new CollisionSystem(*this));
                m_EventQueue.reset(new EventQueue());
                m_States.back().reset(new HomeScreen(*this));
            }

        }
        return true;
    }

    void Engine::PostEvent(const std::shared_ptr<BaseEvent> &Event)
    {
        this->m_EventQueue->PushEvent(Event);
    }

    void Engine::ProcessEvents()
    {
        while (!m_EventQueue->IsEmpty())
        {
            auto Event = m_EventQueue->PopEvent();
            if (!Event.has_value() || !Event.value())
                continue;

            EventDispatcher::GetInstance().Dispatch(Event.value());
        }
    }

    CollisionSystem & Engine::GetCollisionSystem() {
        return *(m_CollisionSystem.get());
    }

    void Engine::Run()
    {
        int Ticks = 0;

        sf::Clock Timer;
        sf::Time Lag = sf::Time::Zero;

        while (m_Window.isOpen() && !m_States.empty())
        {
            Screen &State = this->GetCurrentState();

            sf::Time Elapsed = Timer.restart();

            Lag += Elapsed;
            if (m_reset) Lag = sf::Time::Zero;

            HandleInput();
            m_CollisionSystem->HandleCollisions();
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
