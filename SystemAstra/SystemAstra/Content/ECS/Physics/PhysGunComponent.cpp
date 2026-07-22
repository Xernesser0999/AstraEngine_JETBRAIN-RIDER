#include "PhysGunComponent.h"

#include "PhysicsComponent.h"
#include "../../../Engine/ECS/Input/MouseComponent.h"
#include "../../../Engine/ECS/Render/RenderComponent.h"
#include "../../../Engine/Main/GameEngine.h"

PhysGunComponent::PhysGunComponent(Object* _Owner, std::vector<Object*>& _objects) : Component(_Owner), other(_objects) {

}

PhysGunComponent::~PhysGunComponent() {
    Grabbed = nullptr;
}

void PhysGunComponent::update(float deltaTime) {
    bool leftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (leftPressed && !Checked) {
        if (Grabbed) {
            drop();
        }
        else {
            Check();
        }
        Checked = true;
    }

    if (!leftPressed) {
        Checked = false;
    }

    Move();
}

void PhysGunComponent::drop() {
    Grabbed->setSize({savedSize});
    other.push_back(Grabbed);
    Grabbed = nullptr;
}

void PhysGunComponent::Move() {
    if (Grabbed) {
        auto comp = owner->getComponent<MouseComponent>();
        sf::Vector2f mousePos = comp->getMousePosition();

        float lagFactor = 0.0005f;  

        sf::Vector2f currentPos = Grabbed->getPosition();
        
        sf::Vector2f newPos;
        newPos.x = currentPos.x + (mousePos.x - currentPos.x) * lagFactor;
        newPos.y = currentPos.y + (mousePos.y - currentPos.y) * lagFactor;

        Grabbed->setPosition(newPos);
    }
}

void PhysGunComponent::Check() {
    for (auto it = other.begin(); it != other.end(); ++it) {
        Object* c = *it;
        if (c->hasComponent<PhysicsComponent>() && Intersect(c)) {
            Grabbed = c;
            savedSize = Grabbed->getSize();
            Grabbed->setSize({Grabbed->getSize().x * 1.2f, Grabbed->getSize().y * 1.2f});
            other.erase(it);
            break;
        }
    }
}

bool PhysGunComponent::Intersect(Object* obj) {
    auto comp = owner->getComponent<MouseComponent>();
    if (!comp) {
        return false;
    }
    sf::Vector2f mousePos = comp->getMousePosition();
    sf::Vector2f objPos = obj->getPosition();
    sf::Vector2f objSize = obj->getSize();

    return mousePos.x > objPos.x - objSize.x * 0.5f &&
       mousePos.x < objPos.x + objSize.x * 0.5f &&
       mousePos.y > objPos.y - objSize.y * 0.5f &&
       mousePos.y < objPos.y + objSize.y * 0.5f;

}
