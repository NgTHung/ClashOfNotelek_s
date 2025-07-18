#pragma once
#include <cmath>
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"
namespace Enviroment
{
    const double Velocity = 200;

    const sf::Vector2u ScreenResolution = {1280, 720};
    const std::string GameName = "Clash of Notelek\'s";

    const int FrameLimit = 60;
    const int TickPerSecond = 30;
    const sf::Time TimePerUpdate = sf::seconds(1.f / TickPerSecond);

    const sf::Vector2i BaseLocation = {0, 0};
    const sf::Vector2f SpriteScalingFactor = {4, 4};
    const int BaseSpriteSize = 32;
    const sf::Vector2i SpriteSize = {BaseSpriteSize, BaseSpriteSize};
    const sf::FloatRect SpriteHitBoxOffset = {sf::Vector2f(5.0f,0.0f),sf::Vector2f(22.0f, 32.0f)};

    const std::string FontExtention = ".ttf";
    const std::string FontDirectory = "assets/fonts";
    const std::string ImageTextureExtention = ".png";
    const std::string FormatTextureExtention = ".json";
    const std::string TextureDirectory = "assets/sprite";

    const float VelocityNormalizationValue = (std::sqrt(2) / 2.f);
    const int CharacterMovingFrameCount = 7;
    const int CharacterStandingFrameCount = 5;

    const int ButtonPadding = 5;
    const int DefaultTextureIndex = 0;
    const bool DefaultAttackingState = false;
    const float DefaultAttackingDamage = 50.0f;
    const sf::IntRect DefaultIntRect = {BaseLocation, SpriteSize};
    const int PlayerCollisionLayer = 1;
    const int AttackableLayer = 2;
}
