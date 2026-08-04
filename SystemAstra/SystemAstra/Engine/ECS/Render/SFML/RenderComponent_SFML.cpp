#include "RenderComponent_SFML.h"
#include "../../../Main/GameEngine.h"

// Use this if the render need to follow the camera. If not, use RenderComponent_OpenGL in order to reduce Lag

RenderComponent_SFML::RenderComponent_SFML(Object* _owner, std::string file) : Component(_owner) {
    rect.setPosition(owner->getPosition());
    rect.setSize(owner->getSize());
    
    TX.loadFromFile(file);
    rect.setTexture(&TX);
    
    path = file;
}

void RenderComponent_SFML::render() {
    GameEngine::getWindow()->draw(rect);
}

void RenderComponent_SFML::setTexture(std::string file) {
    TX.loadFromFile(file);
    rect.setTexture(&TX);
}

void RenderComponent_SFML::setcolor(sf::Color color) {
    rect.setFillColor(color);
}

std::string RenderComponent_SFML::getTexturePath() {
    return path;
}
