#pragma once
#include "State/Screen.hpp"
#include "Graphic/Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <set>

class HomeScreen : public Screen
{
public:
    HomeScreen(Engine &g_Engine);
    ~HomeScreen() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleInput();
    bool FixLagUpdate(const sf::Time &DT) override;
    bool IsDashTurn() const;
    bool HandleEvent(std::shared_ptr<BaseEvent> Event) override;

private:
    Character Notelek;
    std::set<sf::Keyboard::Scancode> activeKey;
};