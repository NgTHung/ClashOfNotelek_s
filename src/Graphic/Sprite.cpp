#include "Graphic/Sprite.hpp"

Character::Character() : m_Texture("assets/sprite/Notelek's sprite.png"), m_Sprite(m_Texture)
{
    
}

Character::Character(sf::Vector2f Position, sf::IntRect IntRect) : Character()
{
    this->SetPosition(Position);
    this->SetIntRect(IntRect);
    this->num = 0;
}

void Character::SetPosition(sf::Vector2f NewPosition)
{
    this->m_Sprite.setPosition(NewPosition);
}

void Character::SetIntRect(sf::IntRect NewIntRect)
{
    this->m_Sprite.setTextureRect(NewIntRect);
}

void Character::SetScale(sf::Vector2f Factors)
{
    this->m_Sprite.setScale(Factors);
}

sf::Vector2f Character::GetPosition() const
{
    return this->m_Sprite.getPosition();
}

bool Character::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(this->m_Sprite);
    return true;
}

void Character::Next(){
    this->num = (this->num + 1) % 8;
    sf::IntRect NewIntRect({34 * this->num, 0}, {32, 32});
    SetIntRect(NewIntRect);
}

void Character::Init(){
    this->num = 0;
    sf::IntRect NewIntRect({0, 0}, {32, 32});
    SetIntRect(NewIntRect);
}