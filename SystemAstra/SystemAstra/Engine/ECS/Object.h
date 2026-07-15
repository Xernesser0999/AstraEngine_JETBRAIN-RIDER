#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"



class Object
{
public :
    enum class Team { Player, Enemy, Neutral, Map };
    Team team = Team::Neutral;
    
private:
    sf::Vector2f position;
    sf::Vector2f size;
    std::vector<Component*> components = {};
    std::string name;
    std::string description;
    int layer;
    
public:
    Object();
    Object(Object& other);
    Object(sf::Vector2f _size);
    Object(sf::Vector2f _position, sf::Vector2f _size);
    ~Object();

    void update(float deltaTime);
    void render();

    void addComponent(Component* newComponent);

    template <typename T> T* getComponent()
    {
        for (auto comp : components)
        {
            auto* downcastComponent = dynamic_cast<T*>(comp);
            if (downcastComponent != nullptr)
            {
                return downcastComponent;
            }
        }
        return nullptr;
    }

    template <typename T> bool hasComponent()
    {
        for (auto comp : components)
        {
            if (auto downcastComponent = dynamic_cast<T*>(comp); downcastComponent != nullptr)
            {
                return true;
            }
        }
        return false;
    }

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);
    
    sf::Vector2f getSize();
    void setSize(sf::Vector2f newSize);
    
    void setLayer(int _layer);
    int getLayer();
    
    void setName(std::string _name);
    std::string& getName();
    
    void setDescription(std::string _description);
    std::string& getDescription();
    
    std::vector<Component*>& getVecComponents();
    
};