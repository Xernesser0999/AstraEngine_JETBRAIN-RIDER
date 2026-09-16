#pragma once
#include "../../Object.h"

class GameEngine;

class ObjectExplorer : public Component {
public:
    std::vector<Object*> List;
    
    sf::Vector2f size;
    sf::Vector2f offset;
    
    Object* Rect;
    Object* Actual;

    std::string currentTexturePath; // texture actuellement sélectionnée dans la palette
    
public:
    ObjectExplorer(Object* _object);
    ~ObjectExplorer() override;
    
    void update(float deltaTime) override;
    void render() override;
    
    void load();
};