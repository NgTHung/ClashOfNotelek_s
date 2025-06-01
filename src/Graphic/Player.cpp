#include "Graphic/Player.hpp"
#include "Utility/Logger.hpp"
#include "Resources/ResourcesManager.hpp"

Player::Player(const sf::RenderWindow &Window) : m_Name(ResourcesManager::GetManager().GetFontHolder().GetFont("arial.ttf")), m_Names({"TTP", "TLTH", "BBQ"})
{
    m_PlayerState = std::make_unique<StandingState>();
    m_Index = 0;
    m_Name.setString(m_Names[m_Index]);
    m_Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_Name.setFillColor(sf::Color::Blue);
    m_TextBound = m_Name.getLocalBounds();
    m_Name.setOrigin(m_TextBound.getCenter());
    m_Name.setPosition(static_cast<sf::Vector2f>(Window.getSize()) / 2.f);
    m_CurrentPosition = m_Name.getPosition();
}

bool Player::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(this->m_Name);
    return true;
}

bool Player::Update(const sf::Time &DT)
{
    if (auto NewState = m_PlayerState->Update(*this, DT))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::HandleEvent()
{
    while (!m_EventQueue.IsEmpty())
    {
        auto TopEvent = m_EventQueue.PopEvent();
        if (!TopEvent.has_value())
            continue;
        switch (TopEvent->get()->GetEventType())
        {
        case GlobalEventType::Generic:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::GameQuit:
        {
            continue;
        }
        case GlobalEventType::PlayerAction:
        {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::PlayerMoved:
        case GlobalEventType::PlayerAttacked:
        {
            this->m_PlayerState->AddEvent(TopEvent.value());
            TopEvent.reset();
            continue;
        }
        default:
        {
            throw "Incorrect populated Event";
        }
        }
    }
    if (auto NewState = m_PlayerState->HandleEvent(*this))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::HandleInput(const std::optional<sf::Event> &Event)
{
    if (auto NewState = m_PlayerState->HandleInput(*this, Event))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::FixLagUpdate(const sf::Time &DT)
{
    if (auto NewState = m_PlayerState->FixLagUpdate(*this, DT))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::setPosition(sf::Vector2f NewPosition)
{
    this->m_Name.setPosition(NewPosition);
    this->m_TextBound = this->m_Name.getLocalBounds();
    this->m_CurrentPosition = NewPosition;
    return true;
}

void Player::ChangeState(std::unique_ptr<PlayerState> NewState)
{
    if (NewState == m_PlayerState || NewState == nullptr)
    {
        return;
    }
    m_PlayerState.reset();
    m_PlayerState = std::move(NewState);
}

sf::Vector2f Player::GetPosition() const
{
    return m_CurrentPosition;
}

void Player::AddEvent(const std::shared_ptr<BaseEvent> &Event)
{
    this->m_EventQueue.PushEvent(Event);
}

void Player::SetName(const std::string &Name)
{
    this->m_Name.setString(Name);
}

void Player::AdvanceIndex()
{
    (m_Index += 1) %= 3;
    this->m_Name.setString(this->m_Names[m_Index]);
}
void Player::ResetIndex()
{
    m_Index = -1;
}
