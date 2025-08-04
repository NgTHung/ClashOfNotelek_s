#pragma once
#include <SFML/Graphics.hpp>
#include <Graphic/Base.hpp>

#include "Wall.hpp"

class Water
{
private:
    std::vector<std::shared_ptr<Wall>> m_Walls;
    Engine& m_Engine;
public:
    void AddWall(sf::Vector2f Position,sf::Vector2f Size);
    void DrawWalls(sf::RenderTarget& Target);
    Water(Engine& g_Engine);
    ~Water() = default;
};
