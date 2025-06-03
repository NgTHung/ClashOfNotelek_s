#include "Graphic/Player.hpp"
#include "Utility/Logger.hpp"
#include "Resources/ResourcesManager.hpp"
#include <cmath>

Player::Player(const Engine &g_Engine) : m_Engine(g_Engine), m_Name(ResourcesManager::GetManager().GetFontHolder().GetFont("arial.ttf")), m_Names({"TTP", "TLTH", "BBQ"})
{
    m_PlayerState = std::make_unique<StandingState>(*this);
    m_Index = 0;
    m_Name.setString(m_Names[m_Index]);
    m_Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_Name.setFillColor(sf::Color::Blue);
    m_TextBound = m_Name.getLocalBounds();
    m_Name.setOrigin(m_TextBound.getCenter());
    m_Name.setPosition(static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f);
    m_CurrentPosition = m_Name.getPosition();
    m_PlayerState->EnterState();
}

bool Player::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(this->m_Name);
    return true;
}

bool Player::Update(const sf::Time &DT)
{
    if (auto NewState = m_PlayerState->Update(DT))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    switch (Event.get()->GetEventType())
    {
    case GlobalEventType::Generic:
    {
        LOG_ERROR("Incorrect populated Event");
        throw "Incorrect populated Event";
    }
    case GlobalEventType::GameQuit:
    {
        break;
    }
    case GlobalEventType::PlayerAction:
    {
        LOG_ERROR("Incorrect populated Event");
        throw "Incorrect populated Event";
    }
    case GlobalEventType::PlayerMoved:
    case GlobalEventType::PlayerAttacked:
    {
        // this->m_PlayerState->AddEvent(Event.value());
        Event.reset();
        break;
    }
    default:
    {
        throw "Incorrect populated Event";
    }
    }
    // if (auto NewState = m_PlayerState->HandleEvent(*this))
    // {
    //     ChangeState(std::move(NewState));
    // }
    return false;
}

bool Player::HandleInput(const std::optional<sf::Event> &Event)
{
    if (auto NewState = m_PlayerState->HandleInput(Event))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Player::FixLagUpdate(const sf::Time &DT)
{
    if (auto NewState = m_PlayerState->FixLagUpdate(DT))
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

void Player::ChangeState(std::unique_ptr<BaseState<Player>> NewState)
{
    if (NewState == m_PlayerState || NewState == nullptr)
    {
        return;
    }
    if (m_PlayerState)
    {
        m_PlayerState->ExitState();
    }
    m_PlayerState.reset();
    m_PlayerState = std::move(NewState);
    if (m_PlayerState)
    {
        m_PlayerState->EnterState();
    }
}

sf::Vector2f Player::GetPosition() const
{
    return m_CurrentPosition;
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

void Player::AddDirection(const Direction NewDirection)
{
    this->s.insert(NewDirection);
}

void Player::RemoveDirection(const Direction NewDirection)
{
    if (this->s.contains(NewDirection))
        this->s.erase(NewDirection);
}
std::set<Direction> Player::GetDirection()
{
    return this->s;
}