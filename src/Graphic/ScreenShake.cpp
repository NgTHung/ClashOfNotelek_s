#include "Graphic/ScreenShake.hpp"

ScreenShake::ScreenShake()
{
    m_Duration = 0.2f;
    m_Strength = 9.f;
    m_Elapsed = 0.f;
}


void ScreenShake::Start() {
    m_Active = true;
}

sf::View ScreenShake::GetShakeViewUpdate(const sf::Time& DT,sf::View CurrentView)
{
    if (!m_Active) return CurrentView;

    m_Elapsed += DT.asSeconds();
    if (m_Elapsed >= m_Duration) {
        m_Active = false;
        m_Elapsed = 0.f;
        return CurrentView;
    }

    float shakeStrength = m_Strength * (1.0f - (m_Elapsed / m_Duration));
    float offsetX = m_OffsetDist(m_Random) * shakeStrength;
    float offsetY = m_OffsetDist(m_Random) * shakeStrength;

    sf::View shakenView = CurrentView;
    shakenView.move(sf::Vector2f(offsetX, offsetY));

    return shakenView;
}

bool ScreenShake::IsActive() const {
    return m_Active;
}
