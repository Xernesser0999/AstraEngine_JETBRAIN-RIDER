#include "MovementComponent.h"

#include "../../Engine/ECS/Render/RenderComponent.h"
#include "../../Engine/ECS/Object.h"

MovementComponent::MovementComponent(Object* _Owner) : Component(_Owner) {
    
}

void MovementComponent::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        owner->setPosition({owner->getPosition().x + (100 * deltaTime), owner->getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        owner->setPosition({owner->getPosition().x - (100 * deltaTime), owner->getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        owner->setPosition({owner->getPosition().x, owner->getPosition().y - (100 * deltaTime)});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        owner->setPosition({owner->getPosition().x, owner->getPosition().y + (100 * deltaTime)});
    }
    
    auto comp = owner->getComponent<RenderComponent>();
    if (comp) {
        comp->setPosition(owner->getPosition());
    }
}
