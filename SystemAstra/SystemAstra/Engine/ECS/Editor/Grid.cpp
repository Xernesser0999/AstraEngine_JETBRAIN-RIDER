#include "Grid.h"

#include "../../Main/GameEngine.h"

Grid::Grid(Object* _owner, sf::Vector2f TileSize, sf::Vector2f TileNumber) : Component(_owner) {
    float offset = 0;
    
    for (int z = 0; z < TileNumber.x; z++) {
        sf::RectangleShape* line = new sf::RectangleShape({5, TileSize.y * TileNumber.y});
        line->setFillColor(sf::Color::White);
        lineArray.push_back(line);
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
    
}

void Grid::render() {
    for (auto c : lineArray) {
        GameEngine::getWindow()->draw(*c);
    }
}
