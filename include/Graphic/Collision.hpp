#pragma once
#include <SFML/Graphics.hpp>
#include "Graphic/HitBox.hpp"
#include <vector>
#include <cmath>
class CollisionSystem
{
public:
    static CollisionSystem& Getinstance();
    std::vector<sf::Vector2f> GetAxes(const std::vector<sf::Vector2f> &Points);
    sf::Vector2f Project(const std::vector<sf::Vector2f> &Points, const sf::Vector2f &Axis);
    bool CheckSATCollision(const std::vector<sf::Vector2f> &PointsA, const std::vector<sf::Vector2f> &PointsB);
private:
    CollisionSystem();
    
};