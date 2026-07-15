#pragma once
#include <functional>
#include <string>
#include <nlohmann/json.hpp>

class Scene;
class Component;
class Object;
class CapacityReader;
class GameEngine;

using ComponentFactory = std::function<Component*(Object*, const nlohmann::json&, Scene*)>;

using mapState = std::unordered_map<std::string,nlohmann::json>*;

struct FactoriesECS {
    static std::unordered_map <
        std::string,
        ComponentFactory
    > factories;
};
