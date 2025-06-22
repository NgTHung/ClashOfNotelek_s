#include "Graphic/Button.hpp"
#include "Utility/Logger.hpp"
#include "Engine/Engine.hpp"
#include "Utility/Enviroment.hpp"

Button::Button(Engine &g_Engine, const sf::Vector2f &pos) : m_Position(pos), m_Engine(g_Engine)
{
    this->m_Button.setOutlineThickness(1);
    this->m_Button.setOutlineColor(sf::Color::White);
    this->m_Button.setFillColor(sf::Color::Black);
    this->m_Button.setPosition(this->m_Position);
    this->m_Text.setPosition(this->m_Position);
}

Button::Button(Engine &g_Engine, const sf::Vector2f pos, const std::string &value) : Button(g_Engine, pos)
{
    this->m_Text.setString(value);
    this->FixtateButtonSize();
}

Button::Button(Engine &g_Engine, const sf::Vector2f pos, const sf::Texture &texture) : Button(g_Engine, pos)
{
    this->m_Button.setTexture(&texture);
}

Button::Button(Engine &g_Engine, const sf::Vector2f pos, const sf::Texture &texture, const std::string &value) : Button(g_Engine, pos, value)
{
    this->m_Button.setTexture(&texture);
}

bool Button::Render(sf::RenderTarget &renderer) const
{
    renderer.draw(this->m_Button);
    renderer.draw(this->m_Text);
    return true;
}

bool Button::Update(const sf::Time &DT)
{
    return true;
}

bool Button::FixLagUpdate(const sf::Time &DT)
{
    return true;
}

bool Button::SetPosition(const sf::Vector2f &NewPos)
{
    this->m_Button.setPosition(NewPos);
    this->m_Text.setPosition(NewPos);
    return true;
}

bool Button::HandleInput(const sf::Event &event)
{
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2f mPos(sf::Mouse::getPosition(this->m_Engine.GetWindow()));
        if (this->m_Button.getGlobalBounds().contains(mPos))
        {
            m_OnClick();
            LOG_DEBUG("Clicked {} {}\n", mPos.x, mPos.y);
        }
    }
    return true;
}

sf::Vector2f Button::GetSize() const
{
    return this->m_Button.getSize();
}

void Button::SetText(const std::string &value)
{
    this->m_Text.setString(value);
    this->FixtateButtonSize();
}

void Button::SetTexture(const sf::Texture &texture)
{
    this->m_Button.setTexture(&texture);
}

void Button::SetOnClick(std::function<void()> func)
{
    this->m_OnClick = func;
}

void Button::FixtateButtonSize()
{
    this->m_Button.setSize({this->m_Text.getLocalBounds().size.x + Enviroment::ButtonPadding, this->m_Text.getLocalBounds().size.y + Enviroment::ButtonPadding});
}