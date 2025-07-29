#pragma once
#include <set>
#include <SFML/Graphics.hpp>

#include "Base.hpp"
#include "Graphic/Player.hpp"
#include "Graphic/Weapon.hpp"

enum class AnimationTag {
    IDLE_S_W,
    IDLE_S_E,
    IDLE_N_W,
    IDLE_N_E,
    WALK_S_W,
    WALK_S_E,
    WALK_N_W,
    WALK_N_E
};

class Character : public GraphicBase {
private:
    Engine &m_Engine;
    std::unique_ptr<BaseState<Character> > m_CharacterState;
    sf::IntRect m_IntRect;
    int m_Index;
    int m_HP;
    std::set<Direction> s;
    bool isNorth;
    bool isSouth;
    bool isWest;
    bool isEast;
    AnimationTag m_CurrentAnimationTag;
    std::shared_ptr<Weapon> m_Weapon;
    sf::RectangleShape m_Shape;
    int m_MiliSecondUpdate = 0;

public:
    Character(Engine &g_Engine);

    ~Character() = default;

    bool Update(const sf::Time &DT) override;

    bool HandleEvent(std::shared_ptr<BaseEvent> Event);

    bool HandleInput(const sf::Event &Event) override;

    bool FixLagUpdate(const sf::Time &DT) override;

    void SetPosition(const sf::Vector2f &position) override;

    bool SetIntRect(const sf::IntRect &Rect);

    void SetScale(const sf::Vector2f &Factor) override;

    bool SetDirection(Direction NewDirection);

    int AnimationTagToInt() const;

    bool NextFrame(int maxframe,const sf::Time & DT);

    bool ResetIndex();

    // void UpdateSprite();
    bool UpdateAnimationTagIDLE();

    bool UpdateAnimationTagWALK();

    void ChangeState(std::unique_ptr<BaseState<Character> > NewState);

    void AddDirection(const Direction NewDirection);

    void RemoveDirection(const Direction NewDirection);

    Weapon &GetWeapon() const;

    std::set<Direction> GetDirection();

    void draw(sf::RenderTarget &Target, sf::RenderStates States) const override;

    GlobalEventType GetCollisionEventType() const override;

    sf::Vector2f GetSize() const override;
};
