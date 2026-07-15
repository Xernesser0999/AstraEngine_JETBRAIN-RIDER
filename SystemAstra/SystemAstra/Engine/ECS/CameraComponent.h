#pragma once

#include "Object.h"
#include "../Tool/Globals.h"

class GameEngine;

class CameraComponent final : public Component
{
public:
    sf::RectangleShape sizeC;
    sf::Vector2f ScreenSize;
    sf::Vector2f LevelSize;

    sf::Vector2f pos;
    sf::Vector2f ObjectivePos;
    sf::Vector2f LagPos;
    
    float lag;
    bool haslag;

    sf::Vector2f worldPos;
    sf::Vector2f worldSize;

    sf::View* view;

    sf::Vector2f CamPos;
    
    float ShakeTimer;
    float ShakeDuration;
    float ShakeIntensity;
    
    bool isShaking;

public:
    CameraComponent(Object* _owner, bool _hasLag, float lagfactor);
    ~CameraComponent() override;

    void update(float deltaTime) override;
    
    void CameraShake(float intensity, float duration);
};