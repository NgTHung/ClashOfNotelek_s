#pragma once
#include <SFML/Graphics.hpp>
#include <random>
class ScreenShake
{
private:

    float m_Duration;
    float m_Elapsed;
    float m_Strength;
    bool m_Active = false;
    std::default_random_engine m_Random;
    std::uniform_real_distribution<float> m_OffsetDist;
public:
    ScreenShake();
    ~ScreenShake() = default;
    sf::View GetShakeViewUpdate(const sf::Time& DT,sf::View CurrentView);
    void Start();
    bool IsActive();
};