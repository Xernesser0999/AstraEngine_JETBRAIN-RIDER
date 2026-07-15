#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <unordered_map>

#include "../Scene/Scene.h"
#include "../Reader/SceneReader.h"

class GameEngine {
private:
    // Data
    static sf::RenderWindow* window; 
    
    static std::unordered_map<int, std::string> scenes;
    static int idScene;
    static Scene* currentScene;
    static int nextScene;
    
    void initRead();
    
    // Time
    sf::Clock clock;
    float delatTime;
    bool inGame;
    
    // Update
    void updateChangeScene();
    void updateEvent();
    void updateTime();
    void update();
    void render();

public:
    // Character
    static std::string* myWeapon;
    static std::vector<std::string> myCapacity;
    
public:
    
    static sf::RenderWindow* getWindow();
    static std::unordered_map<int, std::string>& getMapScene();
    
    static void setScene(int newScene);
    static Scene* getCurrentScene();
    
    GameEngine();
    ~GameEngine();
    void run();
    
};

