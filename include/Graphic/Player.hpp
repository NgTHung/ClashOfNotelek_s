#pragma once
#include "State/PlayerState.hpp"
#include <set>
#include "Engine/Engine.hpp"

enum class Direction
{
    WEST,
    NORTH,
    EAST,
    SOUTH,
    NONE
};

class Player
{
private:
    const Engine &m_Engine;
    std::unique_ptr<BaseState<Player>> m_PlayerState;
    sf::Text m_Name;
    sf::FloatRect m_TextBound;
    std::vector<std::string> m_Names;
    int m_Index;
    sf::Vector2f m_CurrentPosition;
    EventQueue m_EventQueue;
    int m_HP;
    std::set<Direction> s;

public:
    Player(const Engine &g_Engine);
    ~Player() = default;
    bool Render(sf::RenderTarget &Renderer) const;
    bool Update(const sf::Time &DT);
    bool HandleEvent(std::shared_ptr<BaseEvent> Event);
    bool HandleInput(const std::optional<sf::Event> &Event);
    bool FixLagUpdate(const sf::Time &DT);
    bool setPosition(sf::Vector2f NewPosition);
    void ChangeState(std::unique_ptr<BaseState<Player>> NewState);
    void SetName(const std::string &Name);
    void AdvanceIndex();
    void ResetIndex();
    void AddDirection(const Direction NewDirection);
    void RemoveDirection(const Direction NewDirection);
    std::set<Direction> GetDirection();

    sf::Vector2f GetPosition() const;
};
