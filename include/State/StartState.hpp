#pragma once
#include "BaseState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class StartState : public BaseState
{
public:
    StartState(const sf::RenderWindow &Window);
    ~StartState() override = default;
    bool Render(sf::RenderTarget &Renderer) const override;
    bool Update(const sf::Time &DT) override;
    bool HandleEvent(const std::optional<sf::Event> Event) override;
    bool HandleInput() override;
    bool FixLagUpdate(const sf::Time &DT) override;

private:
    sf::Text Name;
    sf::FloatRect TextBound;
    std::vector<std::string> Names;
    int Index;
};