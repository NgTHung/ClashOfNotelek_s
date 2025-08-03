#include "Graphic/Enemy.hpp"


#include "Engine/Engine.hpp"
#include "Event/CollisionEvent.hpp"
#include "Resources/ResourcesHolder.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Enviroment.hpp"



Slime::Slime(Character& Player, Engine &g_Engine):Enemy(Player,g_Engine)
{
    this->m_Shape.setTexture(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Slime.png"));
    Slime::SetScale(Enviroment::SpriteScalingFactor);
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
    this->m_HP = 100;
    m_Speed = 60;
    m_PatrolRange = 1000;
}

void Slime::UpdateState()
{
    sf::Vector2f PlayerPos = m_Player.GetPosition();
    float distance =  sqrt((PlayerPos.x - m_Shape.getPosition().x)*(PlayerPos.x - m_Shape.getPosition().x) + (PlayerPos.y - m_Shape.getPosition().y)*(PlayerPos.y - m_Shape.getPosition().y));

    if (distance <= 200.0f)
        m_State = EnemyState::Chase;
    else
        m_State = EnemyState::Patrol;
}

void Slime::UpdateAnimation()
{
    sf::IntRect TextureRect = this->m_Shape.getTextureRect();
    if (m_MovingRight)
        TextureRect.position.y = 3*Enviroment::BaseSpriteSize;
    else
        TextureRect.position.y = 2*Enviroment::BaseSpriteSize;
    m_Index = (m_Index + 1) % 7;
    TextureRect.position.x = m_Index*Enviroment::BaseSpriteSize;
    m_Shape.setTextureRect(TextureRect);
}

void Slime::Flash()
{
    m_Index = 0;
    sf::IntRect TextureRect = m_Shape.getTextureRect();
    TextureRect.position.x = m_Index*Enviroment::BaseSpriteSize;
    if (m_MovingRight)
        TextureRect.position.y = 5*Enviroment::BaseSpriteSize;
    else
        TextureRect.position.y = 4*Enviroment::BaseSpriteSize;
    m_Shape.setTextureRect(TextureRect);
}


void Slime::BeHitProcess()
{
    Flash();
    sf::Vector2f PlayerPos = m_Player.GetPosition();
    sf::Vector2f Pos = this->m_Shape.getPosition();
    sf::Vector2f Dir = Pos - PlayerPos;
    m_KnockBackHandler.ApplyVelocity(Dir,Enviroment::KnockBackStrength);
}



bool Slime::Update(const sf::Time &DT)
{
    bool CanUpdateAnimation = false;
    m_MiliSecondUpdate += DT.asMilliseconds();
    if (m_MiliSecondUpdate >= 120)
    {
        CanUpdateAnimation = true;
        m_MiliSecondUpdate -= 120;
    }
    if (m_State == EnemyState::Dying) {
        float dt = DT.asSeconds();
        m_DeathTimer += dt;
        sf::Angle RotationAngle = Transformable::getRotation() + sf::degrees(m_RotationSpeed*dt);
        Slime::SetRotation(RotationAngle.asDegrees());
        Slime::Move(m_KnockBackDirection * m_KnockbackSpeed * dt);

       // Slime::SetPosition(Pos);
        m_Index = -1;
        if (CanUpdateAnimation)
            UpdateAnimation();
        if (m_DeathTimer >= m_DeathDuration) {
            m_State = EnemyState::Dead;
            m_Engine.ShakeScreen();
            return true;
        }
        return false;
    }

    if (m_State == EnemyState::Dead) return true;
    if (m_KnockBackHandler.IsActive())
    {
        sf::Vector2f Pos = this->m_Shape.getPosition();
        m_KnockBackHandler.Update(Pos,DT.asSeconds());
        if (m_Engine.GetCollisionSystem().IsFree(Pos,*this,Enviroment::MapEntityCollisionLayer))
            Slime::SetPosition(Pos);
        else
            this->m_KnockBackHandler.Stop();
        m_Index = -1;
        if (CanUpdateAnimation)
            UpdateAnimation();
        return false;
    }
    this->UpdateState();
    float dt = DT.asSeconds();
    sf::Vector2f PlayerPos = m_Player.GetPosition();
    sf::Vector2f Pos = m_Shape.getPosition();
    switch (m_State)
    {
    case EnemyState::Patrol:
        {
            if (m_MovingRight)
            {
                Pos.x += m_Speed * dt;
                if (Pos.x > m_StartPosition.x + m_PatrolRange)
                    m_MovingRight = false;
            }
            else
            {
                Pos.x -= m_Speed * dt;
                if (Pos.x < m_StartPosition.x - m_PatrolRange)
                    m_MovingRight = true;
            }
            break;
        }
    case::EnemyState::Chase:
        {
            if (PlayerPos.x > Pos.x)
            {
                Pos.x += m_Speed * dt;
                m_MovingRight = true;
            }
            else
            {
                Pos.x -= m_Speed * dt;
                m_MovingRight = false;
            }
            if (PlayerPos.y > Pos.y)
                Pos.y += m_Speed * dt;
            else
                Pos.y -= m_Speed * dt;
            break;
        }
    }
    if (m_Engine.GetCollisionSystem().IsFree(Pos,*this,Enviroment::MapEntityCollisionLayer))
        Slime::SetPosition(Pos);
    else
        m_MovingRight = !m_MovingRight;
    if (CanUpdateAnimation)
        UpdateAnimation();
    return true;
}

void Slime::Move(const sf::Vector2f& direction)
{
    Transformable::move(direction);
    m_Shape.move(direction);
}


bool Slime::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    if (m_KnockBackHandler.IsActive()) return false;
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
                this->BeHitProcess();
                m_Engine.ShakeScreen();
                if (this->m_HP <= 0)
                    this->Die();
            }

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
    m_Shape.setPosition(position);
}

bool Slime::SetIntRect(const sf::IntRect& rect)
{
    return true;
}

void Slime::SetScale(const sf::Vector2f& scale)
{
    GraphicBase::SetScale(scale);
    m_Shape.setScale(scale);
}

void Slime::SetRotation(const float angle)
{
    GraphicBase::SetRotation(angle);
    m_Shape.setRotation(sf::degrees(angle));
}


void Slime::draw(sf::RenderTarget& Target, sf::RenderStates states) const
{
    sf::Text HP(ResourcesManager::GetManager().GetFontHolder().GetFont("arial.ttf"));
    HP.setString(std::to_string(this->m_HP));
    HP.setCharacterSize(24);
    HP.setFillColor(sf::Color::Red);
    HP.setPosition(sf::Vector2f(this->GetPosition().x + 3, this->GetPosition().y + 4));
    Target.draw(HP);
    Target.draw(this->m_Shape);
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

void Slime::Die()
{
    m_State = EnemyState::Dying;

    m_KnockBackDirection =  this->GetPosition() - m_Player.GetPosition();
    float Len = std::sqrt(m_KnockBackDirection.x*m_KnockBackDirection.x + m_KnockBackDirection.y*m_KnockBackDirection.y);
    m_KnockBackDirection /= Len;
    Transformable::setOrigin(sf::Vector2f(15,27));
    m_Shape.setOrigin(sf::Vector2f(15,27));
    Slime::SetPosition(sf::Vector2f(this->GetPosition().x + 15, this->GetPosition().y + 24));
}


