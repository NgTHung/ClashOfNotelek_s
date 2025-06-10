#include "Graphic/Player.hpp"
#include "State/SpriteState.hpp"
#include "Graphic/Sprite.hpp"
#include "Utility/Logger.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Graphic/Sprite.hpp"
#include <cmath>

Character::Character(const Engine &g_Engine) : m_Engine(g_Engine), m_Texture(ResourcesManager::GetManager().GetTextureHolder().GetTexture("hi.png")),m_Sprite(m_Texture)
{
     sf::Vector2f Position = static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f;
    sf:: IntRect IntRect = {{0, 0}, {32, 32}};
    sf::Vector2f Factors = {4.0f, 4.0f};             
    this->SetPosition(Position);
    this->SetIntRect(IntRect);
    this->SetScale(Factors);
    this->m_CharacterState = std::make_unique<CharacterStandingState>(*this);
    
    this->m_CharacterState->EnterState();
   // this->m_HP = 100; // Default HP value
    //set Default Directions
    this->isSouth = true;
    this->isNorth = false;
    this->isWest = true;  
    this->isEast = false;
    framecounter = 0;
    
    //set Default AnimationTag
    this->m_CurrentAnimationTag = AnimationTag::IDLE_S_W;

}
bool Character::SetScale(sf::Vector2f Factor)
{
    this->m_Sprite.setScale(Factor);
    return true;
}
bool Character::SetIntRect(const sf::IntRect &Rect)
{
    this->m_IntRect = Rect;
    this->m_Sprite.setTextureRect(Rect);
    return true;
}   
bool Character::Render(sf::RenderTarget &Renderer) const
{
    Renderer.draw(this->m_Sprite);
    return true;
}


bool Character::Update(const sf::Time &DT)
{
    if (auto NewState = m_CharacterState->Update(DT))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Character::HandleEvent(std::shared_ptr<BaseEvent> Event)
{
    switch (Event.get()->GetEventType())
    {
    case GlobalEventType::Generic:
    {
        LOG_ERROR("Incorrect populated Event");
        throw "Incorrect populated Event";
    }
    case GlobalEventType::GameQuit:
    {
        break;
    }
    case GlobalEventType::PlayerAction:
    {
        LOG_ERROR("Incorrect populated Event");
        throw "Incorrect populated Event";
    }
    case GlobalEventType::CharacterMoved:
    case GlobalEventType::PlayerAttacked:
    {
        // this->m_PlayerState->AddEvent(Event.value());
        Event.reset();
        break;
    }
    default:
    {
        throw "Incorrect populated Event";
    }
    }
    // if (auto NewState = m_PlayerState->HandleEvent(*this))
    // {
    //     ChangeState(std::move(NewState));
    // }
    return false;
}

bool Character::HandleInput(const std::optional<sf::Event> &Event)
{
    if (auto NewState = m_CharacterState->HandleInput(Event))
    {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Character::FixLagUpdate(const sf::Time &DT)
{
    if (auto NewState = m_CharacterState->FixLagUpdate(DT))
    {   
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Character::SetPosition(sf::Vector2f NewPosition)
{
    this->m_CurrentPosition = NewPosition;
    this->m_Sprite.setPosition(NewPosition);
    return true;
}

void Character::ChangeState(std::unique_ptr<BaseState<Character>> NewState)
{
    if (NewState == m_CharacterState || NewState == nullptr)
    {
        return;
    }
    if (m_CharacterState)
    {
        m_CharacterState->ExitState();
    }
    m_CharacterState.reset();
    m_CharacterState = std::move(NewState);
    if (m_CharacterState)
    {
        m_CharacterState->EnterState();
    }
}

sf::Vector2f Character::GetPosition() const
{
    return m_CurrentPosition;
}

bool Character::SetDirection(Direction NewDirection)
{
    switch (NewDirection)
    {
    case Direction::NORTH:
        this->isNorth = true;
        this->isSouth = false;
        break;
    case Direction::SOUTH:
        this->isSouth = true;
        this->isNorth = false;
        break;
    case Direction::WEST:
        this->isWest = true;
        this->isEast = false;
        break;
    case Direction::EAST:
        this->isEast = true;
        this->isWest = false;
        break;
    default:
        LOG_ERROR("Invalid direction");
        return false;
    }
    return true;
}
bool Character::UpdateAnimationTagIDLE()
{
    if (this->isNorth && this->isWest)
    {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_N_W;
    }
    else if (this->isNorth && this->isEast)
    {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_N_E;
    }
    else if (this->isSouth && this->isWest)
    {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_S_W;
    }
    else if (this->isSouth && this->isEast)
    {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_S_E;
    }
    else
    {
        LOG_ERROR("Invalid direction combination");
        return false;
    }
    return true;
}
bool Character::UpdateAnimationTagWALK()
{
    if (this->isNorth && this->isWest)
    {
        this->m_CurrentAnimationTag = AnimationTag::WALK_N_W;
    }
    else if (this->isNorth && this->isEast)
    {
        this->m_CurrentAnimationTag = AnimationTag::WALK_N_E;
    }
    else if (this->isSouth && this->isWest)
    {
        this->m_CurrentAnimationTag = AnimationTag::WALK_S_W;
    }
    else if (this->isSouth && this->isEast)
    {
        this->m_CurrentAnimationTag = AnimationTag::WALK_S_E;
    }
    else
    {
        LOG_ERROR("Invalid direction combination");
        return false;
    }
    return true;
}
int Character::AnimationTagToInt() const
{
    switch (this->m_CurrentAnimationTag)
    {
    case AnimationTag::IDLE_S_W:
        return 0;
    case AnimationTag::IDLE_S_E:
        return 1;
    case AnimationTag::IDLE_N_W:
        return 2;
    case AnimationTag::IDLE_N_E:
        return 3;
    case AnimationTag::WALK_S_W:
        return 4;
    case AnimationTag::WALK_S_E:
        return 5;
    case AnimationTag::WALK_N_W:
        return 6;
    case AnimationTag::WALK_N_E:
        return 7;
    default:
        LOG_ERROR("Invalid animation tag");
        return -1; // Error value
    }
}
bool Character::NextFrame(int maxframe)
{
    int TagNum = AnimationTagToInt();
    m_Index = (m_Index + 1) % maxframe;
    sf::IntRect Rect({32*m_Index,32*TagNum},{32,32});
    this->SetIntRect(Rect);
    return true;
}
bool Character::ResetIndex()
{
    this->m_Index = 0;
    return true;
}
void Character::AddDirection(const Direction NewDirection)
{
    this->s.insert(NewDirection);
}

void Character::RemoveDirection(const Direction NewDirection)
{
    if (this->s.contains(NewDirection))
        this->s.erase(NewDirection);
}
std::set<Direction> Character::GetDirection()
{
    return this->s;
}