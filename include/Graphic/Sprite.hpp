#pragma once
#include "State/SpriteState.hpp"
#include <set>
#include <SFML/Graphics.hpp>
#include "Engine/Engine.hpp"
#include "Graphic/Player.hpp"
#include "Graphic/HitBox.hpp"
#include "Graphic/Weapon.hpp"
enum class AnimationTag
{
    IDLE_S_W,
    IDLE_S_E,
    IDLE_N_W,
    IDLE_N_E,
    WALK_S_W,
    WALK_S_E,
    WALK_N_W,
    WALK_N_E
};
class Character
{
private:
    const Engine &m_Engine;
    std::unique_ptr<BaseState<Character>> m_CharacterState;
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    sf::IntRect m_IntRect;
    int m_Index;
    sf::Vector2f m_CurrentPosition;
    EventQueue m_EventQueue;
    int m_HP;
    std::set<Direction> s;
    bool isNorth;
    bool isSouth;
    bool isWest;
    bool isEast;
    AnimationTag m_CurrentAnimationTag;
    std::unique_ptr<HitBox> m_HitBox;
    std::shared_ptr<Weapon> m_Weapon;

public:
    Character(const Engine &g_Engine);
    ~Character() = default;
    bool Render(sf::RenderTarget &Renderer);
    bool Update(const sf::Time &DT);
    bool HandleEvent(std::shared_ptr<BaseEvent> Event);
    bool HandleInput(const std::optional<sf::Event> &Event);
    bool FixLagUpdate(const sf::Time &DT);
    bool SetPosition(sf::Vector2f NewPosition);
    bool SetIntRect(const sf::IntRect &Rect);
    bool SetScale(sf::Vector2f Factor);
    bool SetDirection(Direction NewDirection);
    int AnimationTagToInt() const;
    bool NextFrame(int maxframe);
    bool ResetIndex();
    void UpdateSprite();
    bool UpdateAnimationTagIDLE();
    bool UpdateAnimationTagWALK();
    void ChangeState(std::unique_ptr<BaseState<Character>> NewState);
    void AddDirection(const Direction NewDirection);
    void RemoveDirection(const Direction NewDirection);
    Weapon& GetWeapon();

    std::set<Direction> GetDirection();
    sf::Vector2f GetPosition() const;
};

