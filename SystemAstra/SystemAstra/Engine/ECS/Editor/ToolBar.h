#pragma once
#include "../Object.h"

class GameEngine;

class ToolBar : public Component {
public:
    sf::RectangleShape rect;

public:
    Object* Bar;
    Object* Quit;
    
public:
    ToolBar(Object* _owner);
    ~ToolBar();
    
    void update(float deltaTime) override;
    void render() override;
};
