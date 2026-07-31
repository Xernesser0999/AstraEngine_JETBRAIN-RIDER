#include "EditorCam.h"

#include "../../../Main/GameEngine.h"
#include "../../Input/MouseComponent.h"
#include <optional>

EditorCam::EditorCam(Object* _owner)  : Component(_owner) {
    view = new sf::View({ WindowSize.x / 2, WindowSize.y / 2 }, WindowSize);
    ScreenSize = WindowSize;
}

EditorCam::~EditorCam()
{
    delete view;
    view = nullptr;
}

void EditorCam::update(float dt) {
    auto comp = owner->getComponent<MouseComponent>();

    sf::Vector2f delta = comp->getMouseDelta();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        CamPos -= delta;
    }
    
    view->setCenter(CamPos);
    GameEngine::getWindow()->setView(*view);
}
