#pragma once
#include <vector>
#include "../ECS/Object.h"
#include "Layer.h"
#include "../ECS/CameraComponent.h"

class GameEngine;
class HealthComponent;
class SceneReader;
class Object;

class Scene {
public:
    enum class State {
        Run,
        Paused,
    };
private:
    Layer myLayer;
    std::vector<Object*> myObjects;
    int idScene;
    
    std::vector<std::string> screenVec;
    std::vector<Object*>* objectsScreen;
    std::string screen;
    std::vector<std::vector<Object*>*> previousScreen;
    
    State state;

public:
    Scene();
    Scene(int _idScene);
    ~Scene();
    
    Layer& getMyLayer();
    std::vector<Object*>& getVecObjects();
    
    std::vector<std::string>& getScreenVec();
    std::vector<Object*>* getObjectsScreen();
    std::vector<std::vector<Object*>*>& getPreviousScreen();
    int& getIdScene();
    State& getState();
    std::string& getCurrentScreen();
    
    void addObject(Object* addObject, int Layer);
    
    void setObjectsScreen(std::vector<Object*>* _objectsScreen);
    void setIdScene(int _idScene);
    void setState(State newState);
    void setScreen(std::string newScreen);
    void setLayer(int Layer);
    
    void clearScreen();
    
    void update(float deltatime);
    void render();
};
