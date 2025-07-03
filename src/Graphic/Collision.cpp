    #include"Graphic/Collision.hpp"
CollisionSystem& CollisionSystem::Getinstance(){
    static CollisionSystem collision;
    return collision;
}
std::vector<sf::Vector2f> CollisionSystem::GetAxes(const std::vector<sf::Vector2f> &Points)
{
    std::vector<sf::Vector2f> Axes;
    for(int i = 0 ; i < Points.size() ;i++){
        int NextIndex = (i + 1) % Points.size();
        sf::Vector2f Vertices = Points[NextIndex] - Points[i];
        sf::Vector2f Normal(-Vertices.y, Vertices.x);
        float Length = sqrt(Normal.x * Normal.x + Normal.y * Normal.y);
        if(Length != 0.0f) Normal /= Length;
        Axes.push_back(Normal);
    }
    return Axes;
}
sf::Vector2f CollisionSystem::Project(const std::vector<sf::Vector2f> &Points, const sf::Vector2f &Axis)
{
    sf::Vector2f res = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    for(int i = 0 ; i < Points.size() ;i++){
        float Projection = Points[i].x * Axis.x + Points[i].y * Axis.y;
        if(Projection < res.x)
            res.x = Projection;
        if(Projection > res.y)
            res.y = Projection;
    }
    return res;
}
bool CollisionSystem::CheckSATCollision(const std::vector<sf::Vector2f> &PointsA, const std::vector<sf::Vector2f> &PointsB)
{
    std::vector<sf::Vector2f> AxesA = GetAxes(PointsA);
    std::vector<sf::Vector2f> AxesB = GetAxes(PointsB);
    for(sf::Vector2f &Axis : AxesA)
    {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if(ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false; 
    }
    for(sf::Vector2f &Axis : AxesB)
    {
        sf::Vector2f ProjectionA = Project(PointsA, Axis);
        sf::Vector2f ProjectionB = Project(PointsB, Axis);
        if(ProjectionA.y < ProjectionB.x || ProjectionB.y < ProjectionA.x)
            return false; 
    }
    return true;
}
