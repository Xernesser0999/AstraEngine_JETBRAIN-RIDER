#include "MouseComponent.h"
#include "../../Main/GameEngine.h"

MouseComponent::MouseComponent(Object* _owner) : Component(_owner) {

}

void MouseComponent::update(float deltaTime) {

}

sf::Vector2f MouseComponent::getMousePosition() {
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*GameEngine::getWindow());
    sf::Vector2f mousePos = GameEngine::getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*GameEngine::getWindow()));
    return mousePos;
}

bool MouseComponent::clicked() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return true;
    }
    return false;
}
