#include "ColliderComponent.h"

#include "../../Engine/Main/GameEngine.h"
#include "MovementComponent.h"

ColliderComponent::ColliderComponent(Object* _owner, std::vector<Object*>& _objects) : Component(_owner), other(_objects) {
    pos = owner->getPosition();
    size = owner->getSize();
}

void ColliderComponent::update(float dt) {
    pos = owner->getPosition();
    
    for (auto c : other) {
        auto comp = c->getComponent<MovementComponent>();
        if (comp) {
            resolveCollision(c);
        }
    }
}

bool ColliderComponent::intersects(Object* object) {
    return object->getPosition().x < pos.x + size.x &&
           object->getPosition().x + object->getSize().x > pos.x &&
           object->getPosition().y < pos.y + size.y &&
           object->getPosition().y + object->getSize().y > pos.y;
}

void ColliderComponent::resolveCollision(Object* object) {
    if (!intersects(object))
        return;

    auto comp = object->getComponent<MovementComponent>();
    if (!comp)
        return;

    sf::Vector2f objPos = object->getPosition();
    sf::Vector2f objSize = object->getSize();

    float overlapX = std::min(objPos.x + objSize.x, pos.x + size.x) - std::max(objPos.x, pos.x);
    float overlapY = std::min(objPos.y + objSize.y, pos.y + size.y) - std::max(objPos.y, pos.y);
    
    float objCenterX = objPos.x + objSize.x / 2.f;
    float objCenterY = objPos.y + objSize.y / 2.f;
    float blockCenterX = pos.x + size.x / 2.f;
    float blockCenterY = pos.y + size.y / 2.f;

    if (overlapX < overlapY) {
        if (objCenterX < blockCenterX)
            objPos.x = pos.x - objSize.x;
        else
            objPos.x = pos.x + size.x;
        comp->VelocityX = 0;
    } else {
        if (objCenterY < blockCenterY)
            objPos.y = pos.y - objSize.y;
        else
            objPos.y = pos.y + size.y;
        comp->VelocityY = 0;
    }

    object->setPosition(objPos);
}
