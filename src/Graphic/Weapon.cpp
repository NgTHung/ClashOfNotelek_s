#include "Graphic/Weapon.hpp"

#include "Engine/Engine.hpp"
#include "Resources/ResourcesManager.hpp"

Weapon::Weapon(const sf::IntRect &Rect) : GraphicBase(sf::Vector2f(Rect.size)),
    m_Rect(Rect) {
}

Sword::Sword(Engine &g_Engine) : m_Shape(sf::Vector2f(Enviroment::DefaultIntRect.size)), Weapon(Enviroment::DefaultIntRect),
                                 m_Engine(g_Engine)
{
    m_Rect = Enviroment::DefaultIntRect;
    m_Rect.position.y = Enviroment::BaseSpriteSize;
    m_Shape.setTextureRect(m_Rect);
    m_Shape.setOrigin(sf::Vector2f(14.0f, 24.0f));
    m_Index = 0;
    m_Attacking = false;
    m_Shape.setTexture(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("sword.png"));
    m_Engine.GetCollisionSystem().AddCollidable(this, Enviroment::PlayerCollisionLayer);
    this->m_Vertices.push_back(sf::Vector2f(m_Rect.position));
    this->m_Vertices.push_back(sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y));
    this->m_Vertices.push_back(sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y + m_Rect.size.y));
    this->m_Vertices.push_back(sf::Vector2f(m_Rect.position.x, m_Rect.position.y + m_Rect.size.y));
}

Sword::~Sword()
{
    m_Engine.GetCollisionSystem().RemoveCollidable(GetID(), Enviroment::PlayerCollisionLayer);
}

void Sword::SetPosition(const sf::Vector2f &position)
{
    setPosition(sf::Vector2f(position.x + 14 * abs(getScale().x),
                             position.y + 24 * abs(getScale().y)));
}

void Sword::SetScale(const sf::Vector2f &Scale)
{
    setScale(Scale);
}

void Sword::RotateToMouse()
{
    if (m_Attacking)
        return;
    sf::Vector2f MousePos = m_Engine.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(m_Engine.GetWindow()));
    sf::Vector2f worldPoint = getTransform().transformPoint({getOrigin().x, getOrigin().y - 1.0f});
    sf::Vector2f direction(MousePos.x - worldPoint.x, MousePos.y - worldPoint.y);
    bool flip = direction.x < 0.f;
    float scaleX = std::abs(getScale().x);
    float scaleY = getScale().y;
    SetScale(flip ? sf::Vector2f(-scaleX, scaleY) : sf::Vector2f(scaleX, scaleY));
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 40.f)
        return;
    angle += 90.f;
    SetRotation(angle);
}

GlobalEventType Sword::GetCollisionEventType() const
{
    return GlobalEventType::SwordCollision;
}

sf::Vector2f Sword::GetSize() const
{
    return sf::Vector2f(m_Rect.size.x * std::abs(getScale().x), m_Rect.size.y * std::abs(getScale().y));
}

bool Sword::Update(const sf::Time &)
{
    if (m_Attacking)
    {
        m_Index = (m_Index + 1) % 5;
    }
    else
    {
        RotateToMouse();
    }
    if (m_Index == 0)
    {
        m_Attacking = false;
    }
    m_Rect.position.x = 0 + m_Index * Enviroment::BaseSpriteSize;
    return true;
}

bool Sword::FixLagUpdate(const sf::Time &)
{
    return true;
}

bool Sword::HandleInput(const sf::Event &Event)
{
    return true;
}

void Sword::SetRotation(const float angle)
{
    setRotation(sf::degrees(angle));
}

void Sword::SetOrigin(const sf::Vector2f &Origin)
{
    setOrigin(Origin);
}

void Sword::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // states.transform *= getTransform();
    target.draw(m_Shape, states);
}

void Sword::Attack()
{
    m_Attacking = true;
}

bool Sword::IsAttacking() const
{
    return m_Attacking;
}

void Sword::SetDamage(const float &damage)
{
    m_Damage = damage;
}

float Sword::GetDamage() const
{
    return m_Damage;
}

std::vector<sf::Vector2f> Sword::GetHitBoxPoint()
{
    return this->GetTransformedPoints();
}
