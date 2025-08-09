#pragma once
#include <cmath>
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Listener.hpp"

namespace Enviroment
{
    const double Velocity = 200;

    const sf::Vector2u ScreenResolution = {1280, 720};
    const std::string GameName = "Clash of Notelek\'s";
    const sf::View DefaultView(sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(Enviroment::ScreenResolution.x,Enviroment::ScreenResolution.y)));

    const int FrameLimit = 120;
    const int TickPerSecond = 30;
    const sf::Time TimePerUpdate = sf::seconds(1.f / TickPerSecond);

    const sf::Vector2i BaseLocation = {0, 0};
    const sf::Vector2f SpriteScalingFactor = {4, 4};
    const sf::Vector2f MapScalingFactor = {1, 1};
    const int BaseSpriteSize = 32;
    const sf::Vector2f CenterPointOfPlayer = sf::Vector2f(16,17);
    const sf::Vector2i SpriteSize = {BaseSpriteSize, BaseSpriteSize};
    const sf::FloatRect SpriteHitBoxOffset = {sf::Vector2f(5.0f,0.0f),sf::Vector2f(22.0f, 32.0f)};

    const std::string FontExtention = ".ttf";
    const std::string FontDirectory = "assets/fonts";
    const std::string ImageTextureExtention = ".png";
    const std::string FormatTextureExtention = ".json";
    const std::string TextureDirectory = "assets/sprite";
    const std::string AudioExtention = ".mp3";
    const std::string AudioDirectory = "assets/audio";

    const float VelocityNormalizationValue = (std::sqrt(2) / 2.f);
    const int CharacterMovingFrameCount = 7;
    const int CharacterStandingFrameCount = 5;

    const int ButtonPadding = 5;
    const int DefaultTextureIndex = 0;
    const bool DefaultAttackingState = false;
    const float DefaultAttackingDamage = 50.0f;
    const sf::IntRect DefaultIntRect = {BaseLocation, SpriteSize};
    const int PlayerCollisionLayer = 1;
    const int EnemyAttackLayer = 4;
    const int MapEntityCollisionLayer = 3;
    const int AttackableLayer = 2;


    const float SwordAttackCooldown = 1.0f;
    const int SwordDame = 10;
    const float KnockBackStrength = 250.0f;

    const std::vector<sf::Vector2f> TreePositions = {
        sf::Vector2f{40,35},
        sf::Vector2f{141,223},
        sf::Vector2f{38,260},
        sf::Vector2f{254,247},
        sf::Vector2f{182,267},
        sf::Vector2f{257,80},
        sf::Vector2f{333,29},
        sf::Vector2f{296,152},
        sf::Vector2f{433,81},
        sf::Vector2f{491,92},
        sf::Vector2f{495,211},
        sf::Vector2f{376,277}
    };

    const std::vector<sf::Vector2f> GrassPositions = {
        sf::Vector2f{76,26},
        sf::Vector2f{113,22},
        sf::Vector2f{41,71},
        sf::Vector2f{37,101},
        sf::Vector2f{124,81},
        sf::Vector2f{155,264},
        sf::Vector2f{210,223},
        sf::Vector2f{264,261},
        sf::Vector2f{276,261},
        sf::Vector2f{264,268},
        sf::Vector2f{277,269},
        sf::Vector2f{347,198},
        sf::Vector2f{359,198},
        sf::Vector2f{429,278},
        sf::Vector2f{508,233},
        sf::Vector2f{492,154},
        sf::Vector2f{484,120},
        sf::Vector2f{511,38}
    };

    const std::vector<sf::Vector2f> TinyGrassPositions = {
        sf::Vector2f{36,112},
        sf::Vector2f{298,13},
        sf::Vector2f{309,36},
        sf::Vector2f{333,47},
        sf::Vector2f{273,54},
        sf::Vector2f{253,95},
        sf::Vector2f{339,146},
        sf::Vector2f{245,146}
    };

    const std::vector<sf::Vector2f> BoxPositions = {
        sf::Vector2f{91,23}
    };

    const std::vector<sf::FloatRect> WaterWall = {
        {sf::Vector2f{0,0},sf::Vector2f{32,300}},
        {sf::Vector2f{33,277},sf::Vector2f{330,24}},
        {sf::Vector2f{33,124},sf::Vector2f{50,38}}  ,
        {sf::Vector2f{111,123},sf::Vector2f{73,39}},
        {sf::Vector2f{142,162},sf::Vector2f{41,52}},
        {sf::Vector2f{228,166},sf::Vector2f{20,48}},
        {sf::Vector2f{248,172},sf::Vector2f{67,42}},
        {sf::Vector2f{337,244},sf::Vector2f{26,33}},
        {sf::Vector2f{294,250},sf::Vector2f{43,27}},
        {sf::Vector2f{290,213},sf::Vector2f{25,6}},
        {sf::Vector2f{315,172},sf::Vector2f{91,16}},
        {sf::Vector2f{362,103},sf::Vector2f{45,69}},
        {sf::Vector2f{141,45},sf::Vector2f{98,48}},
        {sf::Vector2f{363,296},sf::Vector2f{97,5}},
        {sf::Vector2f{460,273},sf::Vector2f{62,28}},
        {sf::Vector2f{522,0},sf::Vector2f{12,300}},
        {sf::Vector2f{502,115},sf::Vector2f{20,73}},
        {sf::Vector2f{32,0},sf::Vector2f{108,7}},
        {sf::Vector2f{140,0},sf::Vector2f{69,13}},
{sf::Vector2f{140,92},sf::Vector2f{43,32}},
{sf::Vector2f{183,148},sf::Vector2f{44,65}},
        {sf::Vector2f{209,0},sf::Vector2f{32,11}},
        {sf::Vector2f{241,0},sf::Vector2f{6,9}},
        {sf::Vector2f{247,0},sf::Vector2f{117,6}},
        {sf::Vector2f{364,0},sf::Vector2f{158,6}},
        {sf::Vector2f{361,6},sf::Vector2f{18,96}},
        {sf::Vector2f{379,63},sf::Vector2f{48,40}}
    };
}
