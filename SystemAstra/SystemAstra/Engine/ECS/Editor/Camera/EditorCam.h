#pragma once

#include "../../Object.h"
#include "../../../Tool/Globals.h"

class GameEngine;

class EditorCam final : public Component
{
public:
    sf::RectangleShape sizeC;
    sf::Vector2f ScreenSize;

    sf::Vector2f pos;

    //sf::Vector2f worldPos;
    //sf::Vector2f worldSize;

    sf::View* view;
    sf::Vector2f CamPos;
    
public:
    bool pressed = false;
    sf::Vector2f savedPos;
    
public:
    EditorCam(Object* _owner);
    ~EditorCam() override;

    void update(float deltaTime) override;
};