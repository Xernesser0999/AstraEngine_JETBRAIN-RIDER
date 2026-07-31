#pragma once
#include "../../Component.h"
#include <SFML/Graphics.hpp>
#include <string>

class RenderComponent_OpenGL : public Component {
private:
    sf::Vector2f position = { 0.0f, 0.0f };
    sf::Vector2f size      = { 50.0f, 50.0f };
    float rotation         = 0.0f;
    int textureLayer       = -1;

public:
    RenderComponent_OpenGL(Object* owner, const std::string& texturePath);
    ~RenderComponent_OpenGL();

    void update(float dt) override;
    void render() override {} // ne fait plus rien : géré par RenderSystem

    void setPosition(const sf::Vector2f& pos) { position = pos; }
    void setSize(const sf::Vector2f& newSize) { size = newSize; }
    void setRotation(float degrees) { rotation = degrees; }
    void setTexture(const std::string& texturePath);

    // Accesseurs pour le RenderSystem
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getSize() const { return size; }
    float getRotation() const { return rotation; }
    int getTextureLayer() const { return textureLayer; }
};