#pragma once
#include "State/Screen.hpp"
#include "Graphic/Player.hpp"
#include "Command/Command.hpp"
#include "Graphic/Button.hpp"
#include <SFML/Graphics.hpp>

class StartScreen : public Screen
{
public:
    StartScreen(Engine &g_Engine);
    ~StartScreen() override = default;
    bool Render(sf::RenderTarget &Renderer) override;
    bool Update(const sf::Time &DT) override;
    bool HandleInput(std::optional<sf::Event> Event) override;
    bool FixLagUpdate(const sf::Time &DT) override;
    bool HandleEvent(std::shared_ptr<BaseEvent> Event) override;
    // Player function
private:
    Button m_StartButton;
};