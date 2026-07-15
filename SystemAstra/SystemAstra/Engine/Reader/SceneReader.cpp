#include "SceneReader.h"
#include "../Main/GameEngine.h"

SceneReader* SceneReader::myInstance = nullptr;

SceneReader::~SceneReader() {
    delete myInstance;
    myInstance = nullptr;
}

void SceneReader::read() {
    readScene();
}

void SceneReader::readScene() {
    std::ifstream scene("Data/Scene/SceneManager.json");
    if (scene.is_open()) {
        nlohmann::json data = nlohmann::json::parse(scene);
        nlohmann::json currentScene = data["Scene"];
        for (auto& s : currentScene) {
            std::string file = s.get<std::string>() + ".json";
            std::string path = "Data/Scene/Scene/" + file;
            std::ifstream currentSceneOpen(path);
            
            if (currentSceneOpen.is_open()) {
                nlohmann::json data2 = nlohmann::json::parse(currentSceneOpen);
                GameEngine::getMapScene()[data2["ID"]] = data2["Name"];
            }
        }
    }
}

Scene* SceneReader::initScene(int idScene) {
    std::string file = GameEngine::getMapScene()[idScene] + ".json";
    std::string path = "Data/Scene/Scene/" + file;
    std::ifstream currentScene(path);
    
    if (currentScene.is_open()) {
        nlohmann::json data = nlohmann::json::parse(currentScene);
    
        Scene* newScene = new Scene(idScene);
        newScene->setLayer(data["Layer"]);
        
        nlohmann::json objects = data["Objects"];
        
        for (auto& obj : objects) {
            Object* newObj = new Object({obj["Position"][0],obj["Position"][1]},{obj["Size"][0],obj["Size"][1]});
            newObj->setName(obj["Name"]);
            newObj->setDescription(obj["Description"]);            
            
            if (obj["Team"] == "Player") {
                newObj->team = Object::Team::Player;
            }
            else if (obj["Team"] == "Enemy") {
                newObj->team = Object::Team::Enemy;
            }
            else if (obj["Team"] == "Map") {
                newObj->team = Object::Team::Map;
            }
            else {
                newObj->team = Object::Team::Neutral;
            }
                    
            for (auto& ecs : obj["ECS"]) {
                std::string name = ecs["Component"];
                if (name == "Clone") {
                    int nbr = ecs["args"][0];
                    continue;
                }
                if (FactoriesECS::factories.count(name)) {
                    newObj->addComponent(FactoriesECS::factories[name](newObj, ecs, newScene));
                } else {
                    std::cerr << "Composant inconnu : " << name << std::endl;
                }
            }
            if (newObj->team != Object::Team::Map) {
                newObj->setLayer(obj["LayerPosition"]);
                newScene->addObject(newObj, newObj->getLayer());
            }
        }
        return newScene;
    }
    return nullptr;
}

std::vector<Object*>* SceneReader::initScreen(std::string nameScreen, Scene* currentScene) {
    std::vector<Object*>* myObjects = new std::vector<Object*>;
    
    std::string file = nameScreen + ".json";
    std::string path = "Data/Scene/Screen/" + file;
    std::ifstream screen(path);
    
    if (screen.is_open()) {
        nlohmann::json data = nlohmann::json::parse(screen);
        
        for (auto& obj : data["Objects"]) {
            Object* newObj = new Object({obj["Position"][0],obj["Position"][1]},{obj["Size"][0],obj["Size"][1]});
            
            if (obj["Team"] == "Player") {
                newObj->team = Object::Team::Player;
            }
            else if (obj["Team"] == "Enemy") {
                newObj->team = Object::Team::Enemy;
            }
            else {
                newObj->team = Object::Team::Neutral;
            }
                    
            for (auto& ecs : obj["ECS"]) {
                std::string name = ecs["Component"];
                        
                if (FactoriesECS::factories.count(name)) {
                    newObj->addComponent(FactoriesECS::factories[name](newObj, ecs, currentScene));
                } else {
                    std::cerr << "Composant inconnu : " << name << std::endl;
                }
            }
            myObjects->push_back(newObj);
        }
    }
    return myObjects;
}


void SceneReader::SceneTestDev() {
    Scene* addScene = new Scene(0);
    addScene->setLayer(2);
    
    Object* Map = new Object({0, 0}, { 1920*2, 1080*2});
}

SceneReader* SceneReader::getInstance() {
    if (myInstance == nullptr) {
        myInstance = new SceneReader();
    }
    return myInstance;
}

