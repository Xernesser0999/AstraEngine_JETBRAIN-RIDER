#include "ToolBar.h"
#include "../../Main/GameEngine.h"
#include "../Button/ButtonComponent_UI.h"
#include "../Render/OpenGL/RenderComponent_OpenGL.h"
#include "../Render/SFML/RenderComponent_SFML.h"
#include "Camera/EditorCam.h"

ToolBar::ToolBar(Object* _owner) : Component(_owner) {
    float x = GameEngine::getWindow()->getSize().x;
    
    Bar = new Object({0, 0}, {x, 30});
    Bar->addComponent(new RenderComponent_SFML(Bar, "Assets/Editor/Bar.png"));
    
    Quit = new Object({x - 45, 5}, {40, 20});
    Quit->addComponent(new ButtonComponent_UI(Quit));
    Quit->addComponent(new RenderComponent_SFML(Quit, "Assets/Editor/Quit.png"));
}

ToolBar::~ToolBar() {
    delete Quit;
    
    Quit = nullptr;
}

void ToolBar::update(float deltaTime) {
    // QUIT BUTTON
    if (Quit->getComponent<ButtonComponent_UI>()->clicked()) {
        GameEngine::getWindow()->close();
    }
    
}

void ToolBar::render() {
    GameEngine::getWindow()->setView(GameEngine::getWindow()->getDefaultView());
    
    Bar->render();
    Quit->render();
    
    
    auto cam = owner->getComponent<EditorCam>();
    GameEngine::getWindow()->setView(*cam->view);
}
