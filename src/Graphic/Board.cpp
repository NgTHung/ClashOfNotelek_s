#include "Graphic/Board.hpp"

#include "Resources/ResourcesManager.hpp"
#include "State/HomeScreen.hpp"
Board::Board(Engine& g_Engine,HomeScreen& homeScreen):GraphicBase(sf::Vector2f(0,0)),m_Sprite(ResourcesManager::GetManager().GetTextureHolder().GetTexture("board.png")),
    m_Engine(g_Engine),
    m_homeScreen(homeScreen),
    m_ContinueButton(m_Engine,sf::Vector2f(0,0),ResourcesManager::GetManager().GetTextureHolder().GetTexture("PlayAgain_button.png")),
    m_ExitButton(m_Engine,sf::Vector2f(0,0),ResourcesManager::GetManager().GetTextureHolder().GetTexture("Exit_button.png"))
{
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(300,250)));
    m_Sprite.setScale(sf::Vector2f(2.f,2.f));

    m_ExitButton.SetOnClick([this]()
    {
       this->m_Engine.CloseWindow();
    });
    m_ContinueButton.SetOnClick([this]()
    {
       this->m_homeScreen.PauseGame();
    });
}
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite);
    target.draw(m_ExitButton);
    target.draw(m_ContinueButton);
}

void Board::SetOrigin(sf::Vector2f origin)
{
    m_Sprite.setOrigin(origin);
}

void Board::SetPosition(const sf::Vector2f& position)
{
    m_Sprite.setPosition(position);
    m_ContinueButton.SetPosition(sf::Vector2f(position.x,position.y - 100));
    m_ExitButton.SetPosition(sf::Vector2f(position.x,position.y + 100));
}


GlobalEventType Board::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool Board::Update(const sf::Time& DT)
{
    m_ExitButton.Update(DT);
    m_ContinueButton.Update(DT);
    return true;
}

bool Board::FixLagUpdate(const sf::Time&)
{
    return true;
}

bool Board::HandleInput(const sf::Event& Event)
{
    m_ExitButton.HandleInput(Event);
    m_ContinueButton.HandleInput(Event);
    return true;
}
