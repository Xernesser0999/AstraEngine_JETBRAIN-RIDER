#include "Factories.h"    
#include "../Scene/Scene.h"
#include "../ECS/Object.h"
#include "../ECS/Component.h"
#include "../Main/GameEngine.h"

// ENGINE INCLUDE
#include "../ECS/Render/OpenGL/RenderComponent_OpenGL.h"
#include "../ECS/Editor/Camera/CameraComponent.h"
#include "../../Content/ECS/ColliderComponent.h"
#include "../ECS/Input/MouseComponent.h"
#include "../ECS/Editor/Grid.h"
#include "../ECS/Editor/Camera/EditorCam.h"

// CONTENT INCLUDE
#include "../../Content/ECS/MovementComponent.h"
#include "../ECS/Editor/ToolBar.h"
#include "../ECS/Editor/TileMapExplorer/TileMapExplorer.h"

std::unordered_map <
    std::string,
    ComponentFactory
> FactoriesECS::factories = {
    // #####################
    // ###### ENGINE #######
    // #####################
    {"Render", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new RenderComponent_OpenGL(obj, ecs["args"][0]);
    }},
    {"Cam", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new CameraComponent(obj, ecs["args"][0], ecs["args"][1]);
    }},
    {"Collider", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new ColliderComponent(obj, currentScene->getVecObjects());
    }},
    {"Mouse", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new MouseComponent(obj);
    }},
    {"Grid", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new Grid(obj, {ecs["args"][0], ecs["args"][1]}, {ecs["args"][2], ecs["args"][3]});
    }},
    {"CamEditor", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new EditorCam(obj);
    }},
    {"ToolBar", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new ToolBar(obj);
    }},
    {"TileExplorer", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new TileMapExplorer(obj);
    }},
    // #####################
    // ###### CONTENT ######
    // #####################
    {"Move", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new MovementComponent(obj);
    }}
};
