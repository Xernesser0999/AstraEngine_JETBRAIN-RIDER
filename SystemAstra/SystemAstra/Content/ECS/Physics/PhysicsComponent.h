#pragma once
#include "../../../Engine/ECS/Component.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent(Object* _Object);
    ~PhysicsComponent() = default;
    
    void update(float deltaTime) override;
};
