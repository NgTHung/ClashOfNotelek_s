#pragma once
#include <Graphic/Base.hpp>
#include <Utility/Logger.hpp>
#include <Graphic/Sprite.hpp>



class Slime: public Enemy
{
private:
        EventDispatcher::EventListener m_Listener;

public:
        Slime(Character& Player,Engine &g_Engine);
        ~Slime() override = default;
        bool Update(const sf::Time& DT) override;
        bool HandleEvent(std::shared_ptr<BaseEvent> Event);
        bool HandleInput(const sf::Event& Event) override;
        bool FixLagUpdate(const sf::Time&DT) override;
        void SetPosition(const sf::Vector2f& position) override;
        bool SetIntRect (const sf::IntRect& rect);
        void Move(const sf::Vector2f& direction);
        void SetScale(const sf::Vector2f& scale) override;
        void SetRotation(const float angle) override;
        void draw(sf::RenderTarget &Target, sf::RenderStates states) const override;
        GlobalEventType GetCollisionEventType() const override;
        float GetYAxisPoint() override;
        void UpdateAnimation();
        void UpdateState();
        void BeHitProcess() override;
        void Flash() override;
        void Die() override;

};
