#include"Graphic/Weapon.hpp"

#include "Resources/ResourcesManager.hpp"

Weapon::Weapon(sf::Texture Texture, const sf::IntRect &Rect): m_Texture(std::move(Texture)),
                                                              m_Rect(Rect), GraphicBase(static_cast<sf::Vector2f>(Rect.size)) {
}

Sword::Sword(Engine &g_Engine): Weapon(ResourcesManager::GetManager().GetTextureHolder().GetTexture("sword.png")),
                                m_Engine(g_Engine) {
    m_Rect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32));
    setOrigin(sf::Vector2f(14.0f, 24.0f));
    m_Index = 0;
    m_Attacking = false;
    this->m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    this->m_vertices.resize(4);
    this->m_vertices[0].position = sf::Vector2f(m_Rect.position.x, m_Rect.position.y);
    this->m_vertices[1].position = sf::Vector2f(m_Rect.position.x, m_Rect.position.y + m_Rect.size.y);
    this->m_vertices[2].position = sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y + m_Rect.size.y);
    this->m_vertices[3].position = sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y);
    this->m_vertices[0].texCoords = sf::Vector2f(m_Rect.position.x, m_Rect.position.y);
    this->m_vertices[1].texCoords = sf::Vector2f(m_Rect.position.x, m_Rect.position.y + m_Rect.size.y);
    this->m_vertices[2].texCoords = sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y + m_Rect.size.y);
    this->m_vertices[3].texCoords = sf::Vector2f(m_Rect.position.x + m_Rect.size.x, m_Rect.position.y);
}

void Sword::SetPosition(const sf::Vector2f &position) {
    setPosition(sf::Vector2f(position.x + 14 * abs(getScale().x),
                                      position.y + 24 * abs(getScale().y)));
}

void Sword::SetScale(const sf::Vector2f &Scale) {
    setScale(Scale);
}

void Sword::RotateToMouse(const Engine &engine) {
    if (m_Attacking) return;
    sf::Vector2f MousePos = engine.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(engine.GetWindow()));
    sf::Vector2f worldPoint = getTransform().transformPoint({
        getOrigin().x, getOrigin().y - 1.0f
    });
    sf::Vector2f direction(MousePos.x - worldPoint.x, MousePos.y - worldPoint.y);
    bool flip = direction.x < 0.f;
    float scaleX = std::abs(getScale().x);
    float scaleY = getScale().y;
    SetScale(flip ? sf::Vector2f(-scaleX, scaleY) : sf::Vector2f(scaleX, scaleY));
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 40.f) return;
    angle += 90.f;
    SetRotation(angle);
}

GlobalEventType Sword::GetCollisionEventType() const {
    return GlobalEventType::SwordCollision;
}

sf::Vector2f Sword::GetSize() const {
    return sf::Vector2f(m_Rect.size.x * std::abs(getScale().x), m_Rect.size.y * std::abs(getScale().y));
}

bool Sword::Update(const sf::Time &) {
    if (m_Attacking) {
        m_Index = (m_Index + 1) % 5;
    }
    if (m_Index == 0) {
        m_Attacking = false;
    }
    return true;
}

bool Sword::FixLagUpdate(const sf::Time &) {
    return true;
}

bool Sword::HandleInput(const sf::Event &Event) {
    if (Event.is<sf::Event::MouseButtonPressed>()) {
        m_Attacking = true;
        m_Index = 0; // Reset index to start the attack animation
        RotateToMouse(this->m_Engine);
    }
    return true;
}

void Sword::SetRotation(const float angle) {
    setRotation(sf::degrees(angle));
}

void Sword::SetOrigin(const sf::Vector2f &Origin) {
    setOrigin(Origin);
}

void Sword::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_Texture;
    target.draw(m_vertices, states);
}


void Sword::Attack() {
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

sf::VertexArray Sword::GetHitBoxPoint() {
    return this->GetTransformedPoints();
}
