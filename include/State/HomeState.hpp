#pragma once
#include "State/BaseState.hpp"
#include "Graphic/Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>

class HomeState : public BaseState
{
public:
    HomeState(const Engine &g_Engine);
    ~HomeState() override = default;
    bool Render(sf::RenderTarget &Renderer) const override;
    bool Update(const sf::Time &DT) override;
    bool HandleEvent(const std::optional<sf::Event> Event) override;
    bool HandleInput() override;
    bool FixLagUpdate(const sf::Time &DT) override;
    bool IsDashTurn() const;

private:
    Character Notelek;
    std::set<sf::Keyboard::Scancode> activeKey;
};