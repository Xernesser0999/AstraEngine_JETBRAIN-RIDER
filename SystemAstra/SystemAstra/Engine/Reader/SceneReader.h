#pragma once
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>

#include "../Factories/Factories.h"

#include "../Scene/Scene.h"
#include "Reader.h"


class GameEngine;

class SceneReader : public Reader {
private:
    static SceneReader* myInstance;
   
    SceneReader() = default;
public:
    virtual ~SceneReader() override;
   
    virtual void read() override;
    void readScene();
   
    Scene* initScene(int idScene);
    std::vector<Object*>* initScreen(std::string nameScreen, Scene* currentScene);
   
    void SceneTestDev();
   
    static SceneReader* getInstance();
};
