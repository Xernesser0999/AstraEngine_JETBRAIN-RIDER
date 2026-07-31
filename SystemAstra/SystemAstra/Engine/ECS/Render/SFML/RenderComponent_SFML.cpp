#include "RenderComponent_SFML.h"
#include "../../../Main/GameEngine.h"

RenderComponent_SFML::RenderComponent_SFML(Object* _owner, std::string file) : Component(_owner) {
    rect.setPosition(owner->getPosition());
    rect.setSize(owner->getSize());
}

void RenderComponent_SFML::render() {
    
}
