#include "Graphic/Water.hpp"
Water::Water(Engine& g_Engine): m_Engine(g_Engine)
{
    m_Walls.clear();
}

void Water::AddWall(sf::Vector2f Position,sf::Vector2f Size)
{
    m_Walls.push_back(std::make_shared<Wall>(m_Engine,Position,Size));
}

void Water::DrawWalls(sf::RenderTarget& Target) const {
    for (auto m : m_Walls)
        Target.draw(*m);
}
