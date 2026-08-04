#pragma once
#include "../Object.h"

class GameEngine;

class Grid : public Component {
public:
    std::vector<sf::RectangleShape*> lineArray;
    std::vector<Object*> List;
    
    sf::Vector2f tilesize;
public:
    Grid(Object* _owner, sf::Vector2f TileSize, sf::Vector2f TileNumber);
    ~Grid();
    
    void update(float deltaTime) override;
    void render() override;
};
