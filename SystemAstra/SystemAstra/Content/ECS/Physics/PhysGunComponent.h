#pragma once
#include "../../../Engine/ECS/Object.h"

class GameEngine;

class PhysGunComponent : public Component {
public:
    Object* Grabbed = nullptr;
    std::vector<Object*>& other;
    
    sf::Vector2f savedSize;

    bool Checked = false;
public:
    PhysGunComponent(Object* _Owner, std::vector<Object*>& _objects);
    ~PhysGunComponent() override;

    void update(float deltaTime) override;

    void grab(Object* obj);
    void drop();
    
    void Check();
    bool Intersect(Object* obj);
    void Move();
};