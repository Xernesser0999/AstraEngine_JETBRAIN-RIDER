#pragma once
#include "../../Object.h"

class GameEngine;

class TileMapExplorer : public Component {
public:
    std::vector<Object*> List;
    
    sf::Vector2f size;
    sf::Vector2f offset;
    
    Object* Rect;
    Object* Actual;
    
public:
    TileMapExplorer(Object* _object);
    ~TileMapExplorer() override;
    
    void update(float deltaTime) override;
    void render() override;
    
    void load();
};
