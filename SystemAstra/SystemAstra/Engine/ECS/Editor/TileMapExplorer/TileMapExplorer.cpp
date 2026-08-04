#include "TileMapExplorer.h"
#include <filesystem>

#include "../Grid.h"
#include "../../Editor/Camera/EditorCam.h"
#include "../../../Main/GameEngine.h"
#include "../../Button/ButtonComponent_UI.h"
#include "../../Render/OpenGL/RenderComponent_OpenGL.h"

#include "../../Render/SFML/RenderComponent_SFML.h"

class EditorCam;

TileMapExplorer::TileMapExplorer(Object* _object) : Component(_object) {
    float y = GameEngine::getWindow()->getSize().y;
    Rect = new Object({0, 30}, {300, y - 30});
    
    Rect->addComponent(new RenderComponent_SFML(Rect, ""));
    Rect->getComponent<RenderComponent_SFML>()->setcolor(sf::Color(80, 80, 80, 255));
    
    load();
}

TileMapExplorer::~TileMapExplorer() {
    for (auto c : List) {
        delete c;
        c = nullptr;
    }
    List.clear();
    
    delete Rect;
    Rect = nullptr;
}

void TileMapExplorer::update(float deltaTime) {
    Actual = new Object({0, 0}, {0, 0});
    Actual->addComponent(new RenderComponent_OpenGL(Actual, ""));
    
    for (auto c : List) {
        if (c->hasComponent<ButtonComponent_UI>()) {
            if (c->getComponent<ButtonComponent_UI>()->clicked()) {
                Actual->getComponent<RenderComponent_OpenGL>()->setTexture(c->getComponent<RenderComponent_SFML>()->getTexturePath());
            }
        }
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (Actual) {
            auto comp = owner->getComponent<Grid>();
            Actual->setPosition({10,10});
            Actual->setSize(comp->tilesize);
            
            comp->List.push_back(Actual);
        }
    }
}

void TileMapExplorer::render() {
    GameEngine::getWindow()->setView(GameEngine::getWindow()->getDefaultView());
    
    Rect->render();
    for (auto tile : List) {
        tile->render();
    }
    
    auto cam = owner->getComponent<EditorCam>();
    GameEngine::getWindow()->setView(*cam->view);
}

void TileMapExplorer::load() {
    const std::string cheminDossier = "Assets/Tilemap";

    float x = 10.f;
    float y = 40.f;
    float taille = 32.f;
    float espacement = 8.f;
    float largeurPanel = Rect->getSize().x;

    for (const auto& entry : std::filesystem::directory_iterator(cheminDossier)) {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();
        if (ext != ".png" && ext != ".jpg" && ext != ".jpeg")
            continue;

        std::string chemin = entry.path().string();

        Object* tile = new Object({x, y}, {taille, taille});
        tile->addComponent(new RenderComponent_SFML(tile, chemin));
        tile->addComponent(new ButtonComponent_UI(tile));

        List.push_back(tile);
        
        x += taille + espacement;
        if (x + taille > largeurPanel) {
            x = 10.f;
            y += taille + espacement;
        }
    }
}
