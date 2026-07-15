#pragma once
#include "../../Engine/ECS/Component.h"

class MovementComponent : public Component {
public :
    float speed = 300;
    
    float VelocityX = 0;
    float VelocityY = 0;
public:
    MovementComponent(Object* _Owner);
    ~MovementComponent() = default;
    
    void update(float deltaTime) override;
};
