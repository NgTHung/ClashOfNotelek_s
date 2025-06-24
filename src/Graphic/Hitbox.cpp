#include"Graphic/HitBox.hpp"
RectangleHitBox::RectangleHitBox(const sf::FloatRect& offset){
    m_Offset = offset;
    m_Shape.setSize(m_Offset.size);
    m_Shape.setOrigin(-m_Offset.position);
}
sf::FloatRect RectangleHitBox::GetGlobalBounds() const {
   return m_Shape.getGlobalBounds();
}
void RectangleHitBox::SetScale(const sf::Vector2f& scale){
    m_Shape.setScale(scale);
}
void RectangleHitBox::SetPosition(const sf::Vector2f& position) {
    this->m_Shape.setPosition(position);
}
void RectangleHitBox::SetRotation(sf::Angle angle) {
    m_Shape.setRotation(angle);
}
std::vector<sf::Vector2f> RectangleHitBox::GetTransformedPoints(){
    sf::Transform t = m_Shape.getTransform();
    std::vector<sf::Vector2f> points;
    points.push_back(t.transformPoint({0,0}));
    points.push_back(t.transformPoint({m_Shape.getSize().x,0}));
    points.push_back(t.transformPoint({0,m_Shape.getSize().y}));
    points.push_back(t.transformPoint({m_Shape.getSize().x,m_Shape.getSize().y}));
    return points;
}
void RectangleHitBox::RenderDebug(sf::RenderTarget& target) const {
    sf::RectangleShape rectShape  = m_Shape;
    rectShape.setFillColor(sf::Color::Transparent);
    rectShape.setOutlineColor(sf::Color::Red);
    rectShape.setOutlineThickness(1.0f);
    target.draw(rectShape);
}
