#pragma once
#include "State/Screen.hpp"
#include "Graphic/Player.hpp"
#include "Command/Command.hpp"
#include "Graphic/Button.hpp"
#include <SFML/Graphics.hpp>

#include "Graphic/LeafFalling.hpp"
#include "Graphic/MapEntity.hpp"

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
    int m_TimeperFrame = 150;
    int m_LastUpdate = 0;
    int m_index = 0;
    sf::Sprite m_Sprite;
    Grass m_Grass;
    GraphicButton m_PlayButton;
    GraphicButton m_ExitButton;
    LeafFalling m_LeafFalling;
};