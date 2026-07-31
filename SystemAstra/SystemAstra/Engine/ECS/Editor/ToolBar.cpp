#include "ToolBar.h"
#include "../../Main/GameEngine.h"
#include "../Button/ButtonComponent_UI.h"
#include "../Render/OpenGL/RenderComponent_OpenGL.h"
#include "Camera/EditorCam.h"

ToolBar::ToolBar(Object* _owner) : Component(_owner) {
    float x = GameEngine::getWindow()->getSize().x;
    rect.setSize({1920, 30});
    rect.setFillColor(sf::Color(88, 88, 88, 255));
    rect.setPosition({0, 0});
    
    Quit = new Object({1920 - 27.5f, 2.5f}, {25, 25});
    Quit->addComponent(new ButtonComponent_UI(Quit));
    Quit->addComponent(new RenderComponent_OpenGL(Quit, "Assets/Debug/Collider_DebugTX.png"));
}

ToolBar::~ToolBar() {
    delete Quit;
    
    Quit = nullptr;
}

void ToolBar::update(float deltaTime) {
    if (Quit->getComponent<ButtonComponent_UI>()->clicked()) {
        GameEngine::getWindow()->close();
    }
}

void ToolBar::render() {
    GameEngine::getWindow()->setView(GameEngine::getWindow()->getDefaultView());
    GameEngine::getWindow()->draw(rect);

    Quit->render();
    
    auto cam = owner->getComponent<EditorCam>();
    GameEngine::getWindow()->setView(*cam->view);
}
