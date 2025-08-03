#pragma once
#include <set>
#include <SFML/Graphics.hpp>

#include "Base.hpp"
#include "SmokeVFX.hpp"
#include "Graphic/Player.hpp"
#include "Graphic/Weapon.hpp"
#include "State/KnockbackHandler.hpp"
#include "Graphic/SmokeVFX.hpp"
#include "SFML/Audio/Listener.hpp"



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

    EventDispatcher::EventListener m_Listener;
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
    sf::Vector2f m_OldPosition;
    std::vector<sf::Vector2f> m_FootVertices;

public:
    Character(Engine &g_Engine);

    ~Character() = default;

    bool Update(const sf::Time &DT) override;

    bool HandleEvent(std::shared_ptr<BaseEvent> Event);

    bool HandleInput(const sf::Event &Event) override;

    bool FixLagUpdate(const sf::Time &DT) override;

    void SetPosition(const sf::Vector2f &position) ;

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

    float GetYAxisPoint() override;

    std::vector<sf::Vector2f> GetFootVertices() const;

};

enum EnemyState
{
    Patrol,
    Chase,
    Dying,
    Dead,
    CanDelete,
    None
};

class Enemy : public GraphicBase
{
public:
    virtual ~Enemy() = default;
    KnockBackHandler m_KnockBackHandler;
    Enemy(Character& Player,Engine &g_Engine);
    void SetStartPosition(const sf::Vector2f& position);
    EnemyState GetState() const;
    virtual void BeHitProcess() = 0;
    virtual void Flash() = 0;
    virtual void Die() = 0;
protected:
    sf::Vector2f m_StartPosition;
    bool m_MovingRight;
    float m_PatrolRange;
    float m_Speed;
    EnemyState m_State;
    Character& m_Player;
    sf::RectangleShape m_Shape;
    sf::IntRect m_TextureRect;
    int m_Index;
    int m_HP;
    Engine& m_Engine;
    float m_Radius;
    int m_LastAttackID;
    HitSmokeVFX m_HitSmokeVFX;
    DeadSmokeVFX m_DeadSmokeVFX;

    //magic number

    float m_DeathTimer = 0.f;
    float m_DeathDuration = .6f;
    float m_RotationSpeed = 1800.f;
    float m_KnockbackSpeed =  500.f;

    sf::Vector2f m_KnockBackDirection;
};
