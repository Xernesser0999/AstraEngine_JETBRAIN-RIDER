#include "Grid.h"
#include "../../Main/GameEngine.h"

Grid::Grid(Object* _owner, sf::Vector2f TileSize, sf::Vector2f TileNumber) : Component(_owner) {
    float offset = -2.5;
    
    tilesize = TileSize;
    
    for (int z = 0; z < TileNumber.x; z++) {
        sf::RectangleShape* line = new sf::RectangleShape({1.5, TileSize.y * TileNumber.y});
        line->setPosition({offset, 0});
        line->setFillColor(sf::Color({255, 255,255,100}));
        lineArray.push_back(line);
        offset += TileSize.x;
    }
    
    offset = -2.5;
    
    for (int z = 0; z < TileNumber.y; z++) {
        sf::RectangleShape* line = new sf::RectangleShape({TileSize.x * TileNumber.x, 1.5});
        line->setPosition({0, offset});
        line->setFillColor(sf::Color({255, 255,255,100}));
        lineArray.push_back(line);
        offset += TileSize.y;
    }
}

Grid::~Grid() {
    for (auto c : lineArray) {
        delete c;
        c = nullptr;
    }
    
    lineArray.clear();
}

void Grid::update(float deltaTime) {
    for (auto c : List) {
        c->update(deltaTime);
    }
}

void Grid::render() {
    for (auto c : lineArray) {
        GameEngine::getWindow()->draw(*c);
    }
    for (auto c : List) {
        c->render();
    }
}
