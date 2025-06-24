#include"Graphic/HitBox.hpp"
RectangleHitBox::RectangleHitBox(const sf::FloatRect& offset){
    m_Offset = offset;
    m_Shape.setSize(m_Offset.size);
    m_Shape.setOrigin(-m_Offset.position);
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
std::vector<sf::Vector2f> RectangleHitBox::GetTransformedPoints() const{
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

QuarterCircleHitBox::QuarterCircleHitBox(const float& Radius,const sf::Vector2f& Center):
    m_Radius(Radius), m_Rotation(sf::degrees(0)), m_Center(Center), m_Scale(0.0f,0.0f), m_Segment(12) {}

void QuarterCircleHitBox::SetPosition(const sf::Vector2f& position){
   m_Center = position; 
}

void QuarterCircleHitBox::SetRotation(sf::Angle angle){
    m_Rotation = angle;
}

void QuarterCircleHitBox::SetScale(const sf::Vector2f& scale){
    m_Scale = scale;
}

std::vector<sf::Vector2f> QuarterCircleHitBox::GetTransformedPoints() const {
    std::vector<sf::Vector2f> Points;
    sf::Transform transform;
    transform.translate(m_Center);
    transform.rotate(m_Rotation);
    transform.scale(m_Scale);
    Points.push_back(transform.transformPoint({0.f, 0.f}));
    const float angleStep = 90.f / static_cast<float>(m_Segment);

     for (int i = 0; i <= m_Segment; ++i) {
        float angleDeg = i * angleStep;
        float angleRad = angleDeg *  std::numbers::pi_v<float>/ 180.f;

        float x = std::cos(angleRad) * m_Radius;
        float y = -std::sin(angleRad) * m_Radius;

        Points.push_back(transform.transformPoint({x, y}));
    }
    return Points;  
}

void QuarterCircleHitBox::RenderDebug(sf::RenderTarget& target) const {
    std::vector<sf::Vector2f> Points = GetTransformedPoints();
    sf::VertexArray shape(sf::PrimitiveType::LineStrip,Points.size() + 1);
    for (size_t i = 0; i < Points.size(); ++i) {
        shape[i].position = Points[i];
        shape[i].color = sf::Color::Red;
    }
    shape[Points.size()].position = Points[0];
    shape[Points.size()].color = sf::Color::Red;
    target.draw(shape);
}
sf::Angle QuarterCircleHitBox::GetRotation() const{
    return m_Rotation;
}