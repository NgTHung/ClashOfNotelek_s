#pragma once
#include "Base.hpp"
#include "Button.hpp"
#include"SFML/Graphics.hpp"

class HomeScreen;
class Board: public GraphicBase
{
public:
    Board(Engine& g_Engine,HomeScreen& homeScreen);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    GlobalEventType GetCollisionEventType() const override;
    bool Update(const sf::Time&) override;
    void SetPosition(const sf::Vector2f& position) override;
    void SetOrigin(sf::Vector2f origin) override;
    bool HandleInput(const sf::Event&) override;
private:
    HomeScreen& m_homeScreen;
    Engine& m_Engine;
    sf::Sprite m_Sprite;
    GraphicButton m_ContinueButton;
    GraphicButton m_ExitButton;
};
