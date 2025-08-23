#pragma once

#include "Graphic/Base.hpp"
#include "State/Screen.hpp"
#include "functional"

class Engine;

class Button : public GraphicBase
{
public:
    Button(Engine &g_Engine, sf::Vector2f, const std::string &);
    Button(Engine &g_Engine, sf::Vector2f, const sf::Texture &);
    Button(Engine &g_Engine, sf::Vector2f, const sf::Texture &, const std::string &);
    ~Button() override = default;

    bool Update(const sf::Time &) override;
    void SetPosition(const sf::Vector2f &) override;
    bool HandleInput(const sf::Event &) override;

    sf::Vector2f GetSize() const override;

    void SetText(const std::string &);
    void SetScale(const sf::Vector2f& ScalingFactor) override;
    void SetTexture(const sf::Texture &);
    void SetOnClick(std::function<void()> func);

    void FixtateButtonSize();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Button(Engine &g_Engine, const sf::Vector2f         &);

public:
    GlobalEventType GetCollisionEventType() const override;

protected:
    sf::RectangleShape m_Button;
    ArielText m_Text;
    sf::Vector2f m_Position;
    std::function<void()> m_OnClick;
    Engine &m_Engine;
};

class GraphicButton: public Button
{
protected:
    int m_Index = 0;
    bool m_HasClicked = false;
    int m_MilliSecondsCount = 0;
    int m_FramePerSecond = 150;

public:
    GraphicButton(Engine &g_Engine, const sf::Vector2f &, const sf::Texture &);
    ~GraphicButton() override = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool HandleInput(const sf::Event &event) override;
    bool Update(const sf::Time &time) override;

};