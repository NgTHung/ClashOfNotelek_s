#pragma once

#include "Event/Event.hpp"

class Collidable;

class CollisionEvent : public BaseEvent {
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;

public:
    CollisionEvent(Collidable* &A, Collidable* &B);
    GlobalEventType GetEventType() const override;
    Collidable* GetCollidableA() const;
    Collidable* GetCollidableB() const;
};

class PlayerCollisionEvent : public CollisionEvent {
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;

public:
    GlobalEventType GetEventType() const override;
    PlayerCollisionEvent(Collidable* &A, Collidable* &B);
};

class WallCollisionEvent : public CollisionEvent {
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;

public:
    WallCollisionEvent(Collidable* &A, Collidable* &B);
    GlobalEventType GetEventType() const override;
};

class EnemyCollisionEvent : public CollisionEvent {
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;

public:
    EnemyCollisionEvent(Collidable* &A, Collidable* &B);
    GlobalEventType GetEventType() const override;
};

class SwordCollisionEvent : public CollisionEvent
{
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;
public:
    SwordCollisionEvent(Collidable* &A, Collidable* &B);
    GlobalEventType GetEventType() const override;
};

class MapEntityCollisionEvent : public CollisionEvent
{
private:
    Collidable* m_CollidableA;
    Collidable* m_CollidableB;
public:
    MapEntityCollisionEvent(Collidable* &A, Collidable* &B);
    GlobalEventType GetEventType() const override;
};
