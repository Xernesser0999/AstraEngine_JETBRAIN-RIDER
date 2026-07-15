#include "Factories.h"    
#include "../Scene/Scene.h"
#include "../ECS/Object.h"
#include "../ECS/Component.h"
#include "../Main/GameEngine.h"

#include "../ECS/Render/RenderComponent.h"
#include "../../Content/ECS/MovementComponent.h"

std::unordered_map <
    std::string,
    ComponentFactory
> FactoriesECS::factories = {
    {"Render", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new RenderComponent(obj, ecs["args"][0]);
    }},
    {"Move", [](Object* obj, const nlohmann::json& ecs, Scene* currentScene) -> Component* {
        return new MovementComponent(obj);
    }}
};