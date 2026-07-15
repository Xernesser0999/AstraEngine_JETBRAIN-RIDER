#pragma once
#include <SFML/Graphics.hpp>

class Object;

class Component {
protected:
    Object* owner;

public:
    Component(Object* _owner);
    virtual ~Component() = default;
    
    Object* getOwner() const { return owner; }

    virtual void update(float deltaTime);
    virtual void render();
};