#pragma once
#include "State/ScreenState.hpp"
#include "Graphic/Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <set>

class HomeState : public ScreenState
{
public:
    HomeState(const Engine &g_Engine);
    ~HomeState() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleEvent(const std::optional<sf::Event> Event);
    bool HandleInput();
    bool FixLagUpdate(const sf::Time &DT) override;
    bool IsDashTurn() const;

private:
    Character Notelek;
    std::set<sf::Keyboard::Scancode> activeKey;
};