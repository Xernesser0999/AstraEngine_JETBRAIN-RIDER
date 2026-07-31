#include "ButtonComponent_UI.h"
#include "../../Main/GameEngine.h"

ButtonComponent_UI::ButtonComponent_UI(Object* _owner) : Component(_owner) {
    pos = owner->getPosition();
    size = owner->getSize();
    
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(sf::Color::White);
}

void ButtonComponent_UI::update(float deltaTime) {
    
}

bool ButtonComponent_UI::clicked() {
    sf::Vector2f worldPos = GameEngine::getWindow()->mapPixelToCoords(
        sf::Mouse::getPosition(*GameEngine::getWindow()),
        GameEngine::getWindow()->getDefaultView());
    if (rect.getGlobalBounds().contains(worldPos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return true;
        }
    }
    return false;
}

bool ButtonComponent_UI::hovered() {
    sf::Vector2f worldPos = GameEngine::getWindow()->mapPixelToCoords(
        sf::Mouse::getPosition(*GameEngine::getWindow()),
        GameEngine::getWindow()->getDefaultView());
    if (rect.getGlobalBounds().contains(worldPos)) {
        return true;
    }
    return false;
}

void ButtonComponent_UI::render() {
    GameEngine::getWindow()->draw(rect);
}
