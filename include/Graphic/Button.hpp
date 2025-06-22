#pragma once

#include "Graphic/Base.hpp"
#include "State/Screen.hpp"
#include "functional"

class Engine;

class Button : public GraphicBase
{
public:
    Button(Engine &g_Engine, const sf::Vector2f, const std::string &);
    Button(Engine &g_Engine, const sf::Vector2f, const sf::Texture &);
    Button(Engine &g_Engine, const sf::Vector2f, const sf::Texture &, const std::string &);

    bool Render(sf::RenderTarget &) const override;
    bool Update(const sf::Time &) override;
    bool FixLagUpdate(const sf::Time &) override;
    bool SetPosition(const sf::Vector2f &) override;
    bool HandleInput(const sf::Event &) override;

    sf::Vector2f GetSize() const override;
    
    void SetText(const std::string &);
    void SetTexture(const sf::Texture &);
    void SetOnClick(std::function<void()> func);
    
    void FixtateButtonSize();

private:
    Button(Engine &g_Engine, const sf::Vector2f &);
    sf::RectangleShape m_Button;
    ArielText m_Text;
    sf::Vector2f m_Position;
    std::function<void()> m_OnClick;
    Engine &m_Engine;
};