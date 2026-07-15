#include "GameEngine.h"
#include <optional>

sf::RenderWindow* GameEngine::window = nullptr;
std::unordered_map<int, std::string> GameEngine::scenes;
Scene* GameEngine::currentScene;
int GameEngine::idScene = 0;
int GameEngine::nextScene = 0;
std::string* GameEngine::myWeapon = nullptr;
std::vector<std::string> GameEngine::myCapacity;

#include <glad/glad.h>

GameEngine::GameEngine() {
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Project-X");
    
    window->setActive(true);
    
    if (!gladLoadGL()) {
        throw std::runtime_error("Échec du chargement de GLAD");
    }
    
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
    currentScene->render();
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
