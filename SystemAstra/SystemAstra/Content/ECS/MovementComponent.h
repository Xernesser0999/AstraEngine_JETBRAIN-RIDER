#pragma once
#include "../../Engine/ECS/Component.h"

class MovementComponent : public Component {
public :
    float speed = 100;
    
public:
    MovementComponent(Object* _Owner);
    ~MovementComponent() = default;
    
    void update(float deltaTime) override;
};
