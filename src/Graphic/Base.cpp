#include "Graphic/Base.hpp"
#include "Resources/ResourcesManager.hpp"

ArielText::ArielText() : Text(ResourcesManager::GetManager().GetFontHolder().GetFont("arial.ttf"))
{
    setCharacterSize(25);
    setOutlineColor(sf::Color::Black);
    setFillColor(sf::Color::White);
}