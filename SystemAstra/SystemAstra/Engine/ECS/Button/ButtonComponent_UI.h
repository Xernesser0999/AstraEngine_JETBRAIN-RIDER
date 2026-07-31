#pragma once
#include "../Object.h"

class GameEngine;

class ButtonComponent_UI : public Component {
public:
    sf::Vector2f pos;
    sf::Vector2f size;
    
    sf::RectangleShape rect;

public:
    ButtonComponent_UI(Object* _owner);
    ~ButtonComponent_UI() override = default;

    void update(float deltaTime) override;
    void render() override;
    
    bool clicked();
    bool hovered();
};
