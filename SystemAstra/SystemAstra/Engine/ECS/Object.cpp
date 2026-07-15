#include "Object.h"

Object::Object() : position({0,0}), size({0,0}) , name(""){
}

Object::Object(Object& other) : position(other.getPosition()), size(other.getSize()), name(other.getName()) {
    
}

Object::Object(sf::Vector2f _size)  : size(_size), position({0,0}){
}

Object::Object(sf::Vector2f _position, sf::Vector2f _size)
    : position(_position)
    , size(_size)
{
}

Object::~Object()
{
    for (auto& comp : components)
    {
        delete comp;
        comp = nullptr;
    }
}

void Object::update(float deltaTime)
{
    for (auto& comp : components)
    {
        comp->update(deltaTime);
    }
}

void Object::render()
{
    for (auto& comp : components)
    {
        comp->render();
    }
}

void Object::addComponent(Component* newComponent)
{
    components.push_back(newComponent);
}

sf::Vector2f Object::getPosition()
{
    return position;
}

void Object::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

sf::Vector2f Object::getSize()
{
    return size;
}

void Object::setSize(sf::Vector2f newSize)
{
    size = newSize;
}

void Object::setLayer(int _layer) {
    layer = _layer;
}

int Object::getLayer() {
    return layer;
}

void Object::setName(std::string _name) {
    name = _name;
}

void Object::setDescription(std::string _description) {
    description = _description;
}

std::string& Object::getName() {
    return name;
}

std::string& Object::getDescription() {
    return description;
}

std::vector<Component*>& Object::getVecComponents() {
    return components;
}
