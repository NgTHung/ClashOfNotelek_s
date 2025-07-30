#include "Graphic/Player.hpp"
#include "State/SpriteState.hpp"
#include "Graphic/Sprite.hpp"

#include "Event/CollisionEvent.hpp"
#include "Utility/Logger.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Utility/Enviroment.hpp"

#include <iostream>

Character::Character(Engine &g_Engine) : GraphicBase(static_cast<sf::Vector2f>(Enviroment::SpriteSize)),
                                         m_Engine(g_Engine)
                                           {
    const sf::Vector2f Position = static_cast<sf::Vector2f>(g_Engine.GetWindow().getSize()) / 2.f;
    const sf::IntRect IntRect = {Enviroment::BaseLocation, Enviroment::SpriteSize};
    this->m_Weapon = std::make_shared<Sword>(g_Engine);
    this->m_Weapon->SetScale(Enviroment::SpriteScalingFactor);
    this->Character::SetScale(Enviroment::SpriteScalingFactor);
    this->Character::SetPosition(Position);
    m_OldPosition = {0,0};
    this->SetIntRect(IntRect);
    m_Shape.setSize(Character::GetSize());
    m_Shape.setTexture(&ResourcesManager::GetManager().GetTextureHolder().GetTexture("hi.png"));

    this->m_CharacterState = std::make_unique<CharacterStandingState>(m_Engine, *this);

    this->m_CharacterState->EnterState();
    // this->m_HP = 100; // Default HP value
    // set Default Directions
    this->isSouth = true;
    this->isNorth = false;
    this->isWest = true;
    this->isEast = false;
    // set Default AnimationTag
    this->m_CurrentAnimationTag = AnimationTag::IDLE_S_W;

    this->m_Vertices.resize(4);
    this->m_Vertices[0] = sf::Vector2f{6,0};
    this->m_Vertices[1] = sf::Vector2f{26,0};
    this->m_Vertices[2] = sf::Vector2f{26,32};
    this->m_Vertices[3] = sf::Vector2f{6,32};

    this->m_FootVertices.resize(4);
    this->m_FootVertices[0] = sf::Vector2f{11,29};
    this->m_FootVertices[2] = sf::Vector2f{22,29};
    this->m_FootVertices[3] = sf::Vector2f{22,32};
    this->m_FootVertices[1] = sf::Vector2f{11,32};

    m_Engine.GetCollisionSystem().AddCollidable(this,Enviroment::PlayerCollisionLayer);
    m_Engine.GetCollisionSystem().AddCollidable(this,Enviroment::FootCollisionLayer);

    this->m_Listener = [this](const std::shared_ptr<BaseEvent> &Event) { return this->HandleEvent(Event); };
    EventDispatcher::GetInstance().RegisterListener(
            GlobalEventType::CharacterCollision, m_Listener);
}

Weapon &Character::GetWeapon() const {
    return *m_Weapon;
}

bool Character::SetIntRect(const sf::IntRect &Rect) {
    this->m_IntRect = Rect;
    m_Shape.setTextureRect(this->m_IntRect);
    return true;
}

void Character::SetScale(const sf::Vector2f &Factor) {
    Collidable::SetScale(Factor);
    this->m_Weapon->SetScale(Factor);
}

bool Character::Update(const sf::Time &DT) {
    // m_Sword.RotateToMouse();
    m_Weapon->Update(DT);
    if (auto NewState = m_CharacterState->Update(DT)) {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Character::HandleEvent(std::shared_ptr<BaseEvent> Event) {
    switch (Event.get()->GetEventType()) {
        case GlobalEventType::Generic: {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::GameQuit: {
            break;
        }
        case GlobalEventType::PlayerAction: {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
        case GlobalEventType::CharacterMoved:
        case GlobalEventType::PlayerAttacked: {
            // this->m_PlayerState->AddEvent(Event.value());
            Event.reset();
            break;
        }
        case GlobalEventType::CharacterCollision: {
            auto CollisionEvent = std::dynamic_pointer_cast<PlayerCollisionEvent>(Event);
            if (!CollisionEvent) {
                LOG_ERROR("Failed to cast Event to PlayerCollisionEvent");
                return false;
            }
            Collidable *CollidableA = CollisionEvent->GetCollidableA();
            Collidable *CollidableB = CollisionEvent->GetCollidableB();
            if (!CollidableA || !CollidableB) {
                LOG_ERROR("CollidableA or CollidableB is null in PlayerCollisionEvent");
                return false;
            }
            if (CollidableB->GetID() == this->GetID()) {
                if (CollidableA->GetID() == this->GetID()) {
                    std::swap(CollidableA, CollidableB);
                } else {
                    LOG_ERROR("Neither CollidableA or CollidableB is the Character ID: {}", this->GetID());
                    break;
                }
            }
            switch (CollidableB->GetCollisionEventType()) {
                case GlobalEventType::MapEntityCollision:
                    {
                        if (m_Engine.GetCollisionSystem().CheckSATCollision(this->GetFootVertices(),CollidableB->GetTransformedPoints()))
                        {
                            LOG_DEBUG("Character Foot collided with MapEntity ID: {}", CollidableB->GetID());
                            Character::SetPosition(m_OldPosition);
                        }
                        break;
                    }
                case GlobalEventType::WallCollision: {
                    LOG_DEBUG("Character collided with Wall ID: {}", CollidableB->GetID());
                    Character::SetPosition(m_OldPosition);
                    break;
                }
                case GlobalEventType::EnemyCollision: {
                    LOG_DEBUG("Character collided with Enemy ID: {}", CollidableB->GetID());
                    // Handle enemy collision logic here
                    break;
                }
                case GlobalEventType::CharacterCollision: {
                    LOG_DEBUG("Character collided with another Character ID: {}", CollidableB->GetID());
                    // Handle character collision logic here
                    this->m_HP -= 10;
                    break;
                }
                case GlobalEventType::SwordCollision: {
                    LOG_DEBUG("Character collided with Sword ID: {}", CollidableB->GetID());
                    // Handle sword collision logic here
                    this->m_HP -= 10;
                    break;
                }
                default: {
                    LOG_ERROR("Unhandled collision event type for collidable with ID: {}", CollidableB->GetID());
                    return false;
                }
            }
            break;
        }
        default: {
            LOG_ERROR("Incorrect populated Event");
            throw "Incorrect populated Event";
        }
    }
    // if (auto NewState = m_PlayerState->HandleEvent(*this))
    // {
    //     ChangeState(std::move(NewState));
    // }
    return false;
}

bool Character::HandleInput(const sf::Event &Event) {
    if (auto NewState = m_CharacterState->HandleInput(Event)) {
        ChangeState(std::move(NewState));
    }
    return true;
}

bool Character::FixLagUpdate(const sf::Time &DT) {
    if (auto NewState = m_CharacterState->FixLagUpdate(DT)) {
        ChangeState(std::move(NewState));
    }
    return true;
}

void Character::SetPosition(const sf::Vector2f &position) {
    if (this->m_OldPosition != position)
        this->m_OldPosition = Collidable::GetPosition();
    //m_Shape.setPosition(position);
    Collidable::SetPosition(position);
    this->m_Weapon->SetPosition(position);
}

void Character::ChangeState(std::unique_ptr<BaseState<Character> > NewState) {
    if (NewState == m_CharacterState || NewState == nullptr) {
        return;
    }
    if (m_CharacterState) {
        m_CharacterState->ExitState();
    }
    m_CharacterState.reset();
    m_CharacterState = std::move(NewState);
    if (m_CharacterState) {
        m_CharacterState->EnterState();
    }
}

void Character::draw(sf::RenderTarget &Target, sf::RenderStates States) const {
    States.transform *= GetTransform();
    Target.draw(m_Shape, States);

    std::vector<sf::Vector2f> Points = this->GetTransformedPoints();
    sf::VertexArray shape(sf::PrimitiveType::LineStrip,Points.size() + 1);
    for (size_t i = 0; i < Points.size(); ++i) {
        shape[i].position = Points[i];
        shape[i].color = sf::Color::Red;
    }
    if(Points.size() > 0)
        shape[Points.size()].position = Points[0];
    // for(auto i : Points)
    //     std::cout<< i.x << " " << i.y << '\n';
    Target.draw(shape);
    if (m_Weapon) {
        Target.draw(*m_Weapon, States);
    }
}

GlobalEventType Character::GetCollisionEventType() const {
    return GlobalEventType::CharacterCollision;
}

sf::Vector2f Character::GetSize() const {
    return sf::Vector2f(m_IntRect.size);
}

bool Character::SetDirection(Direction NewDirection) {
    switch (NewDirection) {
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

bool Character::UpdateAnimationTagIDLE() {
    if (this->isNorth && this->isWest) {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_N_W;
    } else if (this->isNorth && this->isEast) {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_N_E;
    } else if (this->isSouth && this->isWest) {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_S_W;
    } else if (this->isSouth && this->isEast) {
        this->m_CurrentAnimationTag = AnimationTag::IDLE_S_E;
    } else {
        LOG_ERROR("Invalid direction combination");
        return false;
    }
    return true;
}

bool Character::UpdateAnimationTagWALK() {
    if (this->isNorth && this->isWest) {
        this->m_CurrentAnimationTag = AnimationTag::WALK_N_W;
    } else if (this->isNorth && this->isEast) {
        this->m_CurrentAnimationTag = AnimationTag::WALK_N_E;
    } else if (this->isSouth && this->isWest) {
        this->m_CurrentAnimationTag = AnimationTag::WALK_S_W;
    } else if (this->isSouth && this->isEast) {
        this->m_CurrentAnimationTag = AnimationTag::WALK_S_E;
    } else {
        LOG_ERROR("Invalid direction combination");
        return false;
    }
    return true;
}

int Character::AnimationTagToInt() const {
    switch (this->m_CurrentAnimationTag) {
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

bool Character::NextFrame(int maxframe,const sf::Time &DT) {
    int TagNum = AnimationTagToInt();
    this->m_MiliSecondUpdate += DT.asMilliseconds();
    if (this->m_MiliSecondUpdate > 150)
    {
        this->m_MiliSecondUpdate -= 150;
        m_Index = (m_Index + 1) % maxframe;
    }
    sf::IntRect Rect(Enviroment::BaseSpriteSize * sf::Vector2i{m_Index, TagNum}, Enviroment::SpriteSize);
    this->SetIntRect(Rect);
    return true;
}

bool Character::ResetIndex() {
    this->m_Index = 0;
    return true;
}

void Character::AddDirection(const Direction NewDirection) {
    this->s.insert(NewDirection);
}

void Character::RemoveDirection(const Direction NewDirection) {
    if (this->s.contains(NewDirection))
        this->s.erase(NewDirection);
}

std::set<Direction> Character::GetDirection() {
    return this->s;
}

float Character::GetYAxisPoint()
{
    sf::Transform tf = Collidable::GetTransform();
    sf::Vector2f tmp = tf.transformPoint(this->m_Vertices[3]);
    return tmp.y;
}

std::vector<sf::Vector2f> Character::GetFootVertices() const
{
    std::vector<sf::Vector2f> tmp;
    sf::Transform tf = this->GetTransform();
    for (auto vertices : m_FootVertices)
        tmp.push_back(tf.transformPoint(vertices));
    return tmp;
}