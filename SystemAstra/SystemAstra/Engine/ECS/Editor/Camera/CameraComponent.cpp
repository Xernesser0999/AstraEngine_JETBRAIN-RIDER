#include "CameraComponent.h"

#include "../../../Main/GameEngine.h"

CameraComponent::CameraComponent(Object* _owner, bool _hasLag, float lagfactor)  : Component(_owner) {
    view = new sf::View({ WindowSize.x / 2, WindowSize.y / 2 }, WindowSize);
    lag = lagfactor;
    ScreenSize = WindowSize;
    LevelSize = levelSize;
    haslag = _hasLag;
}

CameraComponent::~CameraComponent()
{
    delete view;
    view = nullptr;
}

void CameraComponent::update(float dt) {
    if (haslag)
    {
        ObjectivePos = { owner->getPosition().x + owner->getSize().x / 2, owner->getPosition().y + owner->getSize().y / 2 };

        ObjectivePos.x = std::max(ScreenSize.x / 2, std::min(ObjectivePos.x, LevelSize.x - ScreenSize.x / 2));
        ObjectivePos.y = std::max(ScreenSize.y / 2, std::min(ObjectivePos.y, LevelSize.y - ScreenSize.y / 2));

        sf::Vector2f current = view->getCenter();
        current.x += (ObjectivePos.x - current.x) * lag * dt;
        current.y += (ObjectivePos.y - current.y) * lag * dt;

        CamPos = current;
    }
    else
    {
        ObjectivePos = { owner->getPosition().x + owner->getSize().x / 2, owner->getPosition().y + owner->getSize().y / 2 };
        
        ObjectivePos.x = std::max(ScreenSize.x / 2, std::min(ObjectivePos.x, LevelSize.x - ScreenSize.x / 2));
        ObjectivePos.y = std::max(ScreenSize.y / 2, std::min(ObjectivePos.y, LevelSize.y - ScreenSize.y / 2));
        
        CamPos = ObjectivePos;
    }
    
    if (isShaking) {
        ShakeTimer += dt;

        float t = ShakeTimer / ShakeDuration;
        float currentIntensity = ShakeIntensity * (1.f - t);

        CamPos.x += ((std::rand() % 21) - 10) * currentIntensity;
        CamPos.y += ((std::rand() % 21) - 10) * currentIntensity;
        
        CamPos.x = std::clamp(CamPos.x, ScreenSize.x / 2, LevelSize.x - ScreenSize.x / 2);
        CamPos.y = std::clamp(CamPos.y, ScreenSize.y / 2, LevelSize.y - ScreenSize.y / 2);

        if (ShakeTimer >= ShakeDuration)
            isShaking = false;
    }
    
    view->setCenter(CamPos);
    GameEngine::getWindow()->setView(*view);
}

void CameraComponent::CameraShake(float intensity, float duration)
{
    ShakeIntensity = intensity;
    ShakeDuration = duration;
    ShakeTimer = 0.f;
    isShaking = true;
}
