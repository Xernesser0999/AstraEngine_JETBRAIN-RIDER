#include "GameEngine.h"
#include <optional>

#include "../ECS/Render/OpenGL/RenderComponent_OpenGL.h"
#include "../ECS/Render/OpenGL/TextureArrayManager.h"

sf::RenderWindow* GameEngine::window = nullptr;
std::unordered_map<int, std::string> GameEngine::scenes;
Scene* GameEngine::currentScene;
int GameEngine::idScene = 0;
int GameEngine::nextScene = 0;
std::string* GameEngine::myWeapon = nullptr;
std::vector<std::string> GameEngine::myCapacity;

#include <glad/glad.h>

GameEngine::GameEngine() {
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "AstraEngine - ALPHA");
    
    window->setActive(true);
    
    if (!gladLoadGL()) {
        throw std::runtime_error("Échec du chargement de GLAD");
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    TextureArrayManager::get().init(256, 256); // taille de layer, nb max de textures
    RenderSystem::get().init();
    
    delatTime = 0;
    idScene = 0;
    nextScene = -1;
    inGame = true;
    
    
}

GameEngine::~GameEngine() {
    delete myWeapon;
    myWeapon = nullptr;
    
    delete currentScene;
    currentScene = nullptr;
    
    delete window;
    window = nullptr;
}

void GameEngine::initRead() {    
    //Init Save Here
    
    //Init Save End
    SceneReader::getInstance()->read();
    currentScene = SceneReader::getInstance()->initScene(0);
}

void GameEngine::updateChangeScene() {
    if (nextScene == -1) {
        return;
    }
    if (idScene == nextScene) {
        nextScene = -1;
        return;
    }
    idScene = nextScene;
    window->setView(window->getDefaultView());
    delete currentScene;
    currentScene = nullptr;
    currentScene = SceneReader::getInstance()->initScene(idScene);
    if (idScene == 0) {
        myCapacity.clear();
        delete myWeapon;
        myWeapon = nullptr;
    }
}

void GameEngine::updateEvent() {
    while (auto event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        if (event->is<sf::Event::FocusLost>()) {
            inGame = false;
        }
        if (event->is<sf::Event::FocusGained>()) {
            inGame = true;
        }
    }
}

void GameEngine::updateTime() {
    sf::Time elapsed = clock.getElapsedTime();
    clock.restart();
    delatTime = elapsed.asSeconds();
}

void GameEngine::update() {
    currentScene->update(delatTime);
}

void GameEngine::render() {
    RenderSystem::get().renderAll();    // OPENGL
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);

    window->resetGLStates();
    currentScene->render(); // SFML
}


sf::RenderWindow* GameEngine::getWindow() {
    return window;
}

std::unordered_map<int, std::string>& GameEngine::getMapScene() {
    return scenes;
}

void GameEngine::setScene(int newScene) {
    nextScene = newScene;
}

Scene* GameEngine::getCurrentScene() {  
    return currentScene;
}


void GameEngine::run() {
    initRead();
    
    while (window->isOpen()) {
        updateEvent();
        if (inGame) {
            updateChangeScene();
            updateTime();
            update();
            window->clear();
            render();
            window->display();  
        }
    }
}
