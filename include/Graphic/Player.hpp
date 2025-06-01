#pragma once
#include "State/PlayerState.hpp"
#include <SFML/Graphics.hpp>

class Player
{
private:
    std::unique_ptr<PlayerState> m_PlayerState;
    sf::Text m_Name;
    sf::FloatRect m_TextBound;
    std::vector<std::string> m_Names;
    int m_Index;
    sf::Vector2f m_CurrentPosition;
    EventQueue m_EventQueue;

public:
    Player(const sf::RenderWindow &Window);
    ~Player() = default;
    bool Render(sf::RenderTarget &Renderer) const;
    bool Update(const sf::Time &DT);
    bool HandleEvent();
    bool HandleInput(const std::optional<sf::Event> &Event);
    bool FixLagUpdate(const sf::Time &DT);
    bool setPosition(sf::Vector2f NewPosition);
    void ChangeState(std::unique_ptr<PlayerState> NewState);
    void AddEvent(const std::shared_ptr<BaseEvent> &Event);
    void SetName(const std::string &Name);
    void AdvanceIndex();
    void ResetIndex();

    sf::Vector2f GetPosition() const;
};
