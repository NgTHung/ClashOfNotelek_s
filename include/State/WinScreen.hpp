#pragma once
#include "State/Screen.hpp"
#include "Graphic/Button.hpp"
#include "Engine/Engine.hpp"
class WinScreen: public Screen
{
private:
    GraphicButton m_ReplayButton;
    GraphicButton m_ExitButton;
    sf::Sprite m_Sprite;
public:
    WinScreen(Engine &g_Engine);
    ~WinScreen() override = default;
    bool Render(sf::RenderTarget& Renderer) override;
    bool Update(const sf::Time& DT) override;
    bool HandleEvent(std::shared_ptr<BaseEvent> Event) override;
    bool HandleInput(std::optional<sf::Event> Event) override;
};