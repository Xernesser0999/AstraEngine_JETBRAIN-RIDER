#pragma once
#include "../../Component.h"

class GameEngine;

class RenderComponent_SFML : public Component {
public:
    sf::Vector2f pos;
    sf::Vector2f size;
    
    sf::RectangleShape rect;
    sf::Texture TX;
    
public:
    RenderComponent_SFML(Object* _owner, std::string file);
    ~RenderComponent_SFML() override = default;
    
    void render() override;
};
