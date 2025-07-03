#include"Graphic/Weapon.hpp"
Sword::Sword(): m_Texture (ResourcesManager::GetManager().GetTextureHolder().GetTexture("sword.png")), m_Sprite(m_Texture)
{
    m_HitBox = std::make_unique<QuarterCircleHitBox>(16,sf::Vector2f(0,0));
    m_Rect = sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(32,32));
    m_Sprite.setTextureRect(m_Rect);
    m_Sprite.setOrigin(sf::Vector2f(14.0f,24.0f));
    m_Index = 0;
    m_Attacking = false;
}

void Sword::SetPosition(const sf::Vector2f& position){
    m_Sprite.setPosition(sf::Vector2f(position.x + 14*abs(m_Sprite.getScale().x),position.y + 24*abs(m_Sprite.getScale().y)));
    m_HitBox->SetPosition(sf::Vector2f(position.x + 13*abs(m_Sprite.getScale().x),position.y + 24*abs(m_Sprite.getScale().y)));
}

void Sword::SetScale(const sf::Vector2f& Scale){
    m_Sprite.setScale(Scale);
    m_HitBox->SetScale(Scale);
}

void Sword::RotateToMouse(const Engine& engine){
    if(m_Attacking) return;
    sf::Vector2f MousePos = engine.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(engine.GetWindow()));
    sf::Vector2f worldPoint = m_Sprite.getTransform().transformPoint({m_Sprite.getOrigin().x,m_Sprite.getOrigin().y - 1.0f});
    sf::Vector2f direction(MousePos.x - worldPoint.x,MousePos.y - worldPoint.y);
    bool flip = direction.x < 0.f;
    float scaleX = std::abs(m_Sprite.getScale().x);
    float scaleY = m_Sprite.getScale().y;
    SetScale(flip ? sf::Vector2f(-scaleX,scaleY) : sf::Vector2f(scaleX,scaleY));
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;    
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 40.f) return;
    angle += 90.f;
    SetRotation(sf::degrees(angle));
}

void Sword::SetRotation(const sf::Angle& angle){
    m_Sprite.setRotation(angle);
    m_HitBox->SetRotation(angle);
}

void Sword::SetOrigin(const sf::Vector2f& Origin){
    m_Sprite.setOrigin(Origin);
}

void Sword::Render(sf::RenderTarget& Renderer) {
    if(m_Attacking)
        m_Index = (m_Index+1) % 5;
    if(m_Index == 0)
        m_Attacking = false;
    m_Rect = sf::IntRect(sf::Vector2i(0 + 32*m_Index,32),sf::Vector2i(32,32));
    m_Sprite.setTextureRect(m_Rect);
    Renderer.draw(m_Sprite);
}

void Sword::Attack(){
    m_Attacking = true;
}

bool Sword::IsAttacking() const{
    return m_Attacking;
}

void Sword::SetDamage(const float& damage){
    m_Damage = damage;
}

float Sword::GetDamge() const{
    return m_Damage;
}

std::vector<sf::Vector2f> Sword::GetHitBoxPoint(){
    if(this->m_HitBox) return this->m_HitBox->GetTransformedPoints();
    else{
        LOG_ERROR("Weapon HitBox not initialize");
    }
}