#include "Factories.h"    
#include "../Scene/Scene.h"
#include "../ECS/Object.h"
#include "../ECS/Component.h"
#include "../Main/GameEngine.h"

#include "../ECS/Render/RenderComponent.h"
#include "../../Content/ECS/MovementComponent.h"
#include "../ECS/CameraComponent.h"
#include "../../Content/ECS/ColliderComponent.h"
#include "../ECS/Input/MouseComponent.h"
#include "../ECS/Editor/Grid.h"

std::unordered_map <
    std::string,
    ComponentFactory
> FactoriesECS::factories = {
    {"Render", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new RenderComponent(obj, ecs["args"][0]);
    }},
    {"Move", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new MovementComponent(obj);
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
    }}
};
