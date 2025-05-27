#pragma once
#include <SFML/Graphics.hpp>

class Character
{
private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
public:
    Character();
    Character(sf::Vector2f Position);
    ~Character() = default;
    void SetPosition(sf::Vector2f NewPosition);
};