#pragma once
#include <SFML/Graphics.hpp>


class Character
{
private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    int num;
public:
    Character();
    Character(sf::Vector2f Position, sf::IntRect IntRect);
    ~Character() = default;
    //Setter
    void SetPosition(sf::Vector2f NewPosition);
    void SetIntRect(sf::IntRect NewIntRect);
    void SetScale(sf::Vector2f Factors);
    //Getter
    sf::Vector2f GetPosition() const;
    //Other
    bool Render(sf::RenderTarget &Renderer) const;
    void Next();
    void Init();
};