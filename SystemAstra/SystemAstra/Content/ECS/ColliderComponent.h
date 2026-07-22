#pragma once
#include "../../Engine/ECS/Object.h"
class GameEngine;

class ColliderComponent : public Component
{
public:
    
    sf::Vector2f pos;
    sf::Vector2f size;
    
    std::vector<Object*>& other;
public:
    ColliderComponent(Object* _owner, std::vector<Object*>& _objects);
    ~ColliderComponent() override = default;
    
    void update(float dt) override;
    
    bool intersects(Object* object);
    void resolveCollision(Object* object);
};