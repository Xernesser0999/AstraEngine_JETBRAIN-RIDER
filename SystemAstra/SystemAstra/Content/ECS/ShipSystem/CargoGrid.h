#pragma once
#include "../../../Engine/ECS/Object.h"
class GameEngine;

class CargoGrid {
public:
    sf::Vector2f pos;
    sf::Vector2f size;
    
    Object* Render;
    Object* Cargo;
public:
    CargoGrid(sf::Vector2f pos);
    
};
