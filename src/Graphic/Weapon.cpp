#include "Graphic/Weapon.hpp"

#include "Engine/Engine.hpp"
#include "Resources/ResourcesManager.hpp"

int Weapon::s_AttackCount = 0;

Weapon::Weapon(const sf::IntRect &Rect) : GraphicBase(sf::Vector2f(Rect.size)),
                                          m_Rect(Rect) {
}

int Weapon::GetAttackID() const {
    return this->m_AttackID;
}


Sword::Sword(Engine &g_Engine) : Weapon(Environment::DefaultIntRect), m_Engine(g_Engine),
                                 m_Shape(sf::Vector2f(Environment::DefaultIntRect.size)) {
    m_Rect = Environment::DefaultIntRect;
    m_Rect.position.y = Environment::BaseSpriteSize;
    m_Shape.setTextureRect(m_Rect);
    m_Shape.setOrigin(sf::Vector2f(14.0f, 24.0f));
    //setOrigin(sf::Vector2f(14.0f, 24.0f));
    this->Sword::SetDamage(Environment::SwordDame);
    m_Index = 0;
    m_Attacking = false;
    m_Shape.setTexture(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("sword.png"));
    m_Engine.GetCollisionSystem().AddCollidable(this, Environment::AttackableLayer);
}

Sword::~Sword() {
    m_Engine.GetCollisionSystem().RemoveCollidable(GetID(), Environment::PlayerCollisionLayer);
}

void Sword::SetPosition(const sf::Vector2f &position) {
    m_Shape.setPosition(sf::Vector2f(position.x + m_Shape.getOrigin().x * abs(GetScale().x),
                                     position.y + m_Shape.getOrigin().y * abs(GetScale().y)));
    Collidable::SetPosition(sf::Vector2f(position.x + m_Shape.getOrigin().x * abs(GetScale().x),
                                         position.y + m_Shape.getOrigin().y * abs(GetScale().y)));
}

void Sword::SetScale(const sf::Vector2f &Scale) {
    m_Shape.setScale(Scale);
    Collidable::SetScale(Scale);
}

void Sword::RotateToMouse() {
    if (m_Attacking)
        return;
    sf::Vector2f MousePos = m_Engine.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(m_Engine.GetWindow()));
    sf::Vector2f worldPoint = GetTransform().transformPoint({GetOrigin().x, GetOrigin().y - 1.0f});
    sf::Vector2f direction(MousePos.x - worldPoint.x, MousePos.y - worldPoint.y);
    bool flip = direction.x < 0.f;
    float scaleX = std::abs(GetScale().x);
    float scaleY = GetScale().y;
    SetScale(flip ? sf::Vector2f(-scaleX, scaleY) : sf::Vector2f(scaleX, scaleY));
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 40.f)
        return;
    angle += 90.f;
    SetRotation(angle);
}

GlobalEventType Sword::GetCollisionEventType() const {
    return GlobalEventType::SwordCollision;
}

sf::Vector2f Sword::GetSize() const {
    return {m_Rect.size.x * std::abs(GetScale().x), m_Rect.size.y * std::abs(GetScale().y)};
}

bool Sword::Update(const sf::Time &DT) {
    if (m_Attacking) {
        m_Index = (m_Index + 1) % 3;
        float angle = (m_Index == 1 ? 30.0f : 60.0f);
        int Segment = angle / 7;
        float AngleStep = angle / static_cast<float>(Segment);
        if (m_Index == 1) {
            m_Vertices.clear();
            m_Vertices.emplace_back(0, 0);
            m_Vertices.emplace_back(-2, -15);
        } else {
            sf::Vector2f tmp = m_Vertices.back();
            m_Vertices.clear();
            m_Vertices.emplace_back(0, 0);
            m_Vertices.push_back(tmp);
        }
        float AngleStepRad = AngleStep * M_PI / 180.f;
        sf::Vector2f PrevPoint = m_Vertices.back();
        for (int i = 1; i <= Segment; ++i) {
            float x = PrevPoint.x;
            float y = PrevPoint.y;
            sf::Vector2f Rotated;
            Rotated.x = x * std::cos(AngleStepRad) - y * std::sin(AngleStepRad);
            Rotated.y = x * std::sin(AngleStepRad) + y * std::cos(AngleStepRad);
            m_Vertices.push_back(Rotated);
            PrevPoint = Rotated;
        }
    } else {
        if (m_Index != 0)
            m_Index = (m_Index + 1) % 5;
        else
            RotateToMouse();
        m_Vertices.clear();
    }
    if (m_Index == 2) {
        m_Attacking = false;
    }

    m_Rect.position.x = 0 + m_Index * Environment::BaseSpriteSize;
    m_Shape.setTextureRect(m_Rect);
    return true;
}

bool Sword::HandleInput(const sf::Event &Event) {
    return true;
}

void Sword::SetRotation(const float angle) {
    m_Shape.setRotation(sf::degrees(angle));
    Collidable::SetRotation(angle);
}

void Sword::SetOrigin(sf::Vector2f origin) {
    m_Shape.setOrigin(origin);
    Collidable::SetOrigin(origin);
}

void Sword::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // states.transform *= getTransform();
    DrawDebug(target);
    target.draw(m_Shape);
}

void Sword::Attack() {
    m_AttackID = ++s_AttackCount;
    m_Attacking = true;
}

bool Sword::IsAttacking() const {
    return m_Attacking;
}

void Sword::SetDamage(const float &damage) {
    m_Damage = damage;
}

float Sword::GetDamage() const {
    return m_Damage;
}

std::vector<sf::Vector2f> Sword::GetHitBoxPoint() {
    return this->GetTransformedPoints();
}
