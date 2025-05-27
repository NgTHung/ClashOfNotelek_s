#include "Graphic/Sprite.hpp"

Character::Character():m_Texture("assets/sprite/"), m_Sprite(m_Texture){

}

Character::Character(sf::Vector2f Position):Character(){
    this->SetPosition(Position);
}

void Character::SetPosition(sf::Vector2f NewPosition){
    this->m_Sprite.setPosition(NewPosition);
}