#pragma once

#include "../Object.h"

class GameEngine;

class MouseComponent : public Component{
public:
    MouseComponent(Object* owner);
    ~MouseComponent() override = default;
    
    void update(float dt) override;
    
    sf::Vector2f getMousePosition();
    sf::Vector2f getMouseDelta();
    
    bool clicked();
    sf::Vector2f lastPos;
};