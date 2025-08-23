#include "Graphic/LeafFalling.hpp"

#include "Engine/Engine.hpp"
#include "Resources/ResourcesManager.hpp"

Leaf::Leaf(const sf::Texture& tex,const sf::Vector2f& spawnPos,const float& fallSpeed,const float& swingSpeed,const float& swingAmount,const float& rotationSpeed): GraphicBase(sf::Vector2f(0,0)),m_Sprite(tex),m_FallSpeed(fallSpeed),m_RotationSpeed(rotationSpeed),m_StartX(spawnPos.x),m_SwingAmount(swingAmount),m_SwingSpeed(swingSpeed),m_Time(0)
{
    m_Sprite.setPosition(spawnPos);
    m_Sprite.setScale(sf::Vector2f(2.f,2.f));
    m_Sprite.setOrigin(sf::Vector2f(tex.getSize().x/2.f,tex.getSize().y/2.f));
}

void Leaf::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite);
}

GlobalEventType Leaf::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool Leaf::Update(const sf::Time& DT)
{
    float dt = DT.asSeconds();
    m_Time += dt;

    sf::Vector2f pos = m_Sprite.getPosition();
    pos.y += m_FallSpeed * dt;
    pos.x = m_StartX + std::sin(m_Time * m_SwingSpeed) * m_SwingAmount;

    m_Sprite.setPosition(pos);
    m_Sprite.rotate(sf::degrees(m_RotationSpeed * dt));
    return true;
}
sf::Vector2f Leaf::GetPosition() const
{
    return m_Sprite.getPosition();
}
bool Leaf::HandleInput(const sf::Event&)
{
    return true;
}

LeafFalling::LeafFalling(Engine& g_Engine,const sf::FloatRect& spawnArea, const int& leafCount): GraphicBase(sf::Vector2f(0,0)),m_Engine(g_Engine),m_spawnArea(spawnArea)
{
    m_Textures.push_back(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Leaf1.png"));
    m_Textures.push_back(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Leaf2.png"));
    m_Textures.push_back(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Leaf3.png"));
    m_Textures.push_back(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Leaf4.png"));
    m_Textures.push_back(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("Leaf5.png"));
    for (int i = 0; i < leafCount; i++)
        SpawnLeave();
}

void LeafFalling::SpawnLeave()
{
    int idx = rand() % m_Textures.size();

    float x = m_spawnArea.position.x + static_cast<float>(rand() % (int)m_spawnArea.size.x);
    float y = m_spawnArea.position.y + static_cast<float>(rand() % (int)m_spawnArea.size.y);

    float fallSpeed = 50.f + rand() % 60;
    float swingSpeed = 1.5f + (rand() % 200) / 100.f;
    float swingAmount = 20.f + rand() % 30;
    float rotationSpeed = (rand() % 40 - 20);

    m_Leaves.emplace_back(std::make_shared<Leaf>(*m_Textures[idx], sf::Vector2f(x, y), fallSpeed, swingSpeed, swingAmount, rotationSpeed));

}

void LeafFalling::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto & m_Leave : m_Leaves)
        target.draw(*m_Leave);
}

GlobalEventType LeafFalling::GetCollisionEventType() const
{
    return GlobalEventType::Generic;
}

bool LeafFalling::Update(const sf::Time& DT)
{
    for (auto & m_Leave : m_Leaves)
        m_Leave->Update(DT);

    m_Leaves.erase(
          std::remove_if(m_Leaves.begin(), m_Leaves.end(),
              [&](const std::shared_ptr<Leaf>& leaf) {
                  sf::Vector2f pos = leaf->GetPosition();
                  if (pos.y > m_Engine.GetWindow().getSize().y + 50) {
                      SpawnLeave();
                      return true;
                  }
                  return false;
              }),
          m_Leaves.end()
      );

    return false;
}

bool LeafFalling::HandleInput(const sf::Event&)
{
    return true;
}
