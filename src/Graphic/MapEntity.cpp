#include "Graphic/MapEntity.hpp"

#include "Engine/Engine.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Environment.hpp"

Tree::Tree(Engine &g_Engine, const sf::Vector2f &size): GraphicBase(size),
                                                        m_Engine(g_Engine), m_SpriteTree(
                                                            ResourcesManager::GetManager().GetTextureHolder().
                                                            GetTexture("Tree.png")) {
    m_SpriteTree.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(30, 31)));
    Tree::SetScale(sf::Vector2f(10, 10));
    Tree::SetOrigin(sf::Vector2f(9, 27));
    this->m_Vertices.emplace_back(8, 25);
    this->m_Vertices.emplace_back(22, 25);
    this->m_Vertices.emplace_back(22, 30);
    this->m_Vertices.emplace_back(8, 30);
    m_Engine.GetCollisionSystem().AddCollidable(this, Environment::MapEntityCollisionLayer);
}

void Tree::SetPosition(const sf::Vector2f &position) {
    Collidable::SetPosition(position);
    m_SpriteTree.setPosition(position);
}

void Tree::SetOrigin(sf::Vector2f origin) {
    Collidable::SetOrigin(origin);
    m_SpriteTree.setOrigin(origin);
}

void Tree::SetScale(const sf::Vector2f &scale) {
    Collidable::SetScale(scale);
    m_SpriteTree.setScale(scale);
}

bool Tree::Update(const sf::Time &DT) {
    return true;
}

bool Tree::HandleInput(const sf::Event &e) {
    return true;
}

void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_SpriteTree);
    //DrawDebug(target);
}

GlobalEventType Tree::GetCollisionEventType() const {
    return GlobalEventType::MapEntityCollision;
}

float Tree::GetYAxisPoint() {
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(sf::Vector2f(19, 26));
    return tmp.y;
}

//=====================================================================================

Grass::Grass(Engine &g_Engine, const sf::Vector2f &size): GraphicBase(size),
                                                          m_Sprite(
                                                              ResourcesManager::GetManager().GetTextureHolder().
                                                              GetTexture("grass.png")), m_Engine(g_Engine) {
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
    Grass::SetScale(sf::Vector2f(10, 10));
    Grass::SetOrigin(sf::Vector2f(5, 11));
}

void Grass::SetPosition(const sf::Vector2f &position) {
    Collidable::SetPosition(position);
    m_Sprite.setPosition(position);
}

void Grass::SetOrigin(sf::Vector2f origin) {
    Collidable::SetOrigin(origin);
    m_Sprite.setOrigin(origin);
}

void Grass::SetScale(const sf::Vector2f &scale) {
    Collidable::SetScale(scale);
    m_Sprite.setScale(scale);
}

bool Grass::Update(const sf::Time &DT) {
    m_MilliSecondUpdate += DT.asMilliseconds();
    if (m_MilliSecondUpdate >= 120) {
        m_Index = (m_Index + 1) % 10;
        m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(16 * m_Index + 1, 0), sf::Vector2i(16, 16)));
        m_MilliSecondUpdate -= 120;
    }
    return true;
}
bool Grass::HandleInput(const sf::Event &e) {
    return true;
}

void Grass::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite);
    //DrawDebug(target);
}

GlobalEventType Grass::GetCollisionEventType() const {
    return GlobalEventType::Generic;
}

float Grass::GetYAxisPoint() {
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(sf::Vector2f(5, 11));
    return tmp.y;
}

//========================================================================================

TinyGrass::TinyGrass(Engine &g_Engine, const sf::Vector2f &size): GraphicBase(size),
                                                                  m_Engine(g_Engine), m_Sprite(
                                                                      ResourcesManager::GetManager().GetTextureHolder().
                                                                      GetTexture("TinyGrass.png")) {
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
    TinyGrass::SetScale(sf::Vector2f(10, 10));
    TinyGrass::SetOrigin(sf::Vector2f(6, 10));
}

void TinyGrass::SetPosition(const sf::Vector2f &position) {
    Collidable::SetPosition(position);
    m_Sprite.setPosition(position);
}

void TinyGrass::SetOrigin(sf::Vector2f origin) {
    Collidable::SetOrigin(origin);
    m_Sprite.setOrigin(origin);
}

void TinyGrass::SetScale(const sf::Vector2f &scale) {
    Collidable::SetScale(scale);
    m_Sprite.setScale(scale);
}

bool TinyGrass::Update(const sf::Time &DT) {
    m_MilliSecondUpdate += DT.asMilliseconds();
    if (m_MilliSecondUpdate >= 150) {
        m_Index = (m_Index + 1) % 4;
        m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(16 * m_Index + 1, 0), sf::Vector2i(16, 16)));
        m_MilliSecondUpdate -= 120;
    }
    return true;
}

bool TinyGrass::HandleInput(const sf::Event &e) {
    return true;
}

void TinyGrass::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite);
    //DrawDebug(target);
}

GlobalEventType TinyGrass::GetCollisionEventType() const {
    return GlobalEventType::Generic;
}

float TinyGrass::GetYAxisPoint() {
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(sf::Vector2f(6, 10));
    return tmp.y;
}

//==========================================================================
Box::Box(Engine &g_Engine, const sf::Vector2f &size): GraphicBase(size),
                                                      m_Engine(g_Engine), m_Sprite(
                                                          ResourcesManager::GetManager().GetTextureHolder().GetTexture(
                                                              "Box.png")) {
    m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(48, 48)));
    Box::SetScale(sf::Vector2f(10, 10));
    Box::SetOrigin(sf::Vector2f(18, 30));
    this->m_Vertices.emplace_back(17, 24);
    this->m_Vertices.emplace_back(31, 24);
    this->m_Vertices.emplace_back(31, 31);
    this->m_Vertices.emplace_back(17, 31);
    m_Engine.GetCollisionSystem().AddCollidable(this, Environment::MapEntityCollisionLayer);
}

void Box::SetPosition(const sf::Vector2f &position) {
    Collidable::SetPosition(position);
    m_Sprite.setPosition(position);
}

void Box::SetOrigin(sf::Vector2f origin) {
    Collidable::SetOrigin(origin);
    m_Sprite.setOrigin(origin);
}

void Box::SetScale(const sf::Vector2f &scale) {
    Collidable::SetScale(scale);
    m_Sprite.setScale(scale);
}

bool Box::Update(const sf::Time &DT) {
    return true;
}


bool Box::HandleInput(const sf::Event &e) {
    return true;
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite);
    //DrawDebug(target);
}

GlobalEventType Box::GetCollisionEventType() const {
    return GlobalEventType::MapEntityCollision;
}

float Box::GetYAxisPoint() {
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(sf::Vector2f(19, 26));
    return tmp.y;
}

//===============================================================
