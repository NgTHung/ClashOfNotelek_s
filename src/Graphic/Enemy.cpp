#include "Graphic/Enemy.hpp"


#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Enviroment.hpp"

Enemy::Enemy(Engine &g_Engine): GraphicBase(sf::Vector2f(Enviroment::SpriteSize)), m_Engine(g_Engine)
{

}

Slime::Slime(Engine &g_Engine):Enemy(g_Engine)
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
    m_Engine.GetCollisionSystem().AddCollidable(this, Enviroment::AttackableLayer);
    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event) { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
            GlobalEventType::SwordCollision, m_Listener);
    this->m_LastAttackID = -1;
}

bool Slime::Update(const sf::Time &DT)
{
    return true;
}

bool Slime::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    switch (Event.get()->GetEventType())
    {
    case GlobalEventType::Generic: {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
    }
    case GlobalEventType::SwordCollision:
        {

            auto CollisionEvent = std::dynamic_pointer_cast<SwordCollisionEvent>(Event);
            if (!CollisionEvent) {
                LOG_ERROR("Failed to cast Event to SwordCollisionEvent");
                return false;
            }
            Collidable *CollidableA = CollisionEvent->GetCollidableA();
            Collidable *CollidableB = CollisionEvent->GetCollidableB();
            if (!CollidableA || !CollidableB) {
                LOG_ERROR("CollidableA or CollidableB is null in PlayerCollisionEvent");
                return false;
            }
            if (CollidableB->GetID() != this->GetID())
            {
                if (CollidableA->GetID() == this->GetID()) {
                    std::swap(CollidableA, CollidableB);
                } else
                {
                    LOG_ERROR("CollidableA and CollidableB are not match to slime ID");
                    break;
                }
            }
            auto PlayerSword = dynamic_cast<Sword*>(CollidableA);
            if (!PlayerSword)
            {
                LOG_ERROR("Failed to cast ColliableA to Sword");
            }
            if (this->m_LastAttackID != PlayerSword->GetAttackID())
            {
                this->m_LastAttackID = PlayerSword->GetAttackID();
                this->m_HP -= PlayerSword->GetDamage();
            }

        }
        default: {
            LOG_ERROR("Unhandled event type in Slime: {}", static_cast<int>(Event->GetEventType()));
            return false;
        }
    }
    return false;
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
    sf::Text HP(ResourcesManager::GetManager().GetFontHolder().GetFont("arial.ttf"));
    HP.setString(std::to_string(this->m_HP));
    HP.setCharacterSize(24);
    HP.setFillColor(sf::Color::Red);
    HP.setPosition(sf::Vector2f(this->GetPosition().x + 3, this->GetPosition().y + 4));
    Target.draw(HP);
    Target.draw(this->m_Shape, states);
    DrawDebug(Target);
}

GlobalEventType Slime::GetCollisionEventType() const
{
    return GlobalEventType::EnemyCollision;
}

float Slime::GetYAxisPoint()
{
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(this->m_Vertices[3]);
    return tmp.y;
}


