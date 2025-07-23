#include "Graphic/Enemy.hpp"


#include "Engine/Engine.hpp"
#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Enviroment.hpp"

Enemy::Enemy(Engine &g_Engine): m_Engine(g_Engine)
{

}

Slime::Slime(Engine &g_Engine):Enemy(g_Engine),GraphicBase(sf::Vector2f(Enviroment::SpriteSize))
{
    this->m_Shape.setTexture(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Slime.png"));
    Slime::SetScale(Enviroment::SpriteScalingFactor);
    this->m_Shape.setScale(Enviroment::SpriteScalingFactor);
    this->m_Shape.setPosition(sf::Vector2f(0,0));
    Slime::SetPosition(sf::Vector2f(0,0));
    this->m_Shape.setTextureRect(Enviroment::DefaultIntRect);
    this->m_Shape.setSize(Slime::GetSize());
    this->m_Vertices.push_back(sf::Vector2f(4,15));
    this->m_Vertices.push_back(sf::Vector2f(Enviroment::BaseSpriteSize - 6,15));
    this->m_Vertices.push_back(sf::Vector2f(Enviroment::BaseSpriteSize - 6,Enviroment::BaseSpriteSize));
    this->m_Vertices.push_back(sf::Vector2f(4,Enviroment::BaseSpriteSize));
}

bool Slime::Update(const sf::Time &DT)
{

    return true;
}

bool Slime::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    return true;
}

bool Slime::HandleInput(const sf::Event& Event)
{
    return true;
}

bool Slime::FixLagUpdate(const sf::Time& DT)
{
    return true;
}

void Slime::SetPosition(const sf::Vector2f& position)
{
    GraphicBase::SetPosition(position);
}

bool Slime::SetIntRect(const sf::IntRect& rect)
{
    return true;
}

void Slime::SetScale(const sf::Vector2f& scale)
{
    GraphicBase::SetScale(scale);
}

void Slime::draw(sf::RenderTarget& Target, sf::RenderStates states) const
{

    Target.draw(this->m_Shape, states);
    DrawDebug(Target);
}

GlobalEventType Slime::GetCollisionEventType() const
{
    return GlobalEventType::EnemyCollision;
}

