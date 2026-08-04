#include "TileMapExplorer.h"
#include <filesystem>
#include <cmath>

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
    
    Actual = new Object({0, 0}, {0, 0});
    
    load();
}

TileMapExplorer::~TileMapExplorer() {
    for (auto c : List) {
        delete c;
        c = nullptr;
    }
    List.clear();
    
    delete Rect;
    delete Actual;
    
    Rect = nullptr;
    Actual = nullptr;
}

void TileMapExplorer::update(float deltaTime) {
    for (auto c : List) {
        if (c->hasComponent<ButtonComponent_UI>()) {
            if (c->getComponent<ButtonComponent_UI>()->clicked()) {
                currentTexturePath = c->getComponent<RenderComponent_SFML>()->getTexturePath();
                
                for (auto z : List) {
                    z->getComponent<RenderComponent_SFML>()->setcolor(sf::Color(255, 255, 255, 255));
                }
                c->getComponent<RenderComponent_SFML>()->setcolor(sf::Color(255, 255, 255, 50));
            }
        }
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !currentTexturePath.empty()) {
        
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*GameEngine::getWindow());
        if (pixelPos.x < Rect->getSize().x) {
            return;
        }

        auto grid = owner->getComponent<Grid>();
        auto cam  = owner->getComponent<EditorCam>();
        
        sf::Vector2f mouseWorldPos = GameEngine::getWindow()->mapPixelToCoords(pixelPos, *cam->view);
        
        int cellX = static_cast<int>(std::floor(mouseWorldPos.x / grid->tilesize.x));
        int cellY = static_cast<int>(std::floor(mouseWorldPos.y / grid->tilesize.y));
        sf::Vector2f cellPos = { cellX * grid->tilesize.x + grid->tilesize.x / 2, cellY * grid->tilesize.y + grid->tilesize.y / 2};
        
        for (auto it = grid->List.begin(); it != grid->List.end(); ++it) {
            if ((*it)->getPosition() == cellPos) {
                delete *it;
                grid->List.erase(it);
                break;
            }
        }
        
        Object* newTile = new Object(cellPos, grid->tilesize);
        newTile->addComponent(new RenderComponent_OpenGL(newTile, currentTexturePath));
        grid->List.push_back(newTile);
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