#include "MovementComponent.h"

#include "../../Engine/ECS/Render/OpenGL/RenderComponent_OpenGL.h"
#include "../../Engine/ECS/Object.h"

MovementComponent::MovementComponent(Object* _Owner) : Component(_Owner) {
    
}

void MovementComponent::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        speed = 600;
    }
    else {
        speed = 300;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        owner->setPosition({owner->getPosition().x + (speed * deltaTime), owner->getPosition().y});
        VelocityX = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        owner->setPosition({owner->getPosition().x - (speed * deltaTime), owner->getPosition().y});
        VelocityX = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        owner->setPosition({owner->getPosition().x, owner->getPosition().y - (speed * deltaTime)});
        VelocityY = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        owner->setPosition({owner->getPosition().x, owner->getPosition().y + (speed * deltaTime)});
        VelocityY = -1;
    }
}
