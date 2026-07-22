#pragma once
#include "../Component.h"
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <string>

class GameEngine;

class RenderComponent : public Component {
private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int shader = 0;
    unsigned int texture = 0;

    sf::Vector2f position = { 0.0f, 0.0f };
    sf::Vector2f size      = { 50.0f, 50.0f };
    float rotation         = 0.0f;

public:
    RenderComponent(Object* owner, const std::string& texturePath);
    ~RenderComponent();

    void update(float dt) override;
    void render() override;

    void setPosition(const sf::Vector2f& pos);
    void setSize(const sf::Vector2f& newSize);
    void setRotation(float degrees);
    void setTexture(std::string texturePath);

private:
    void initGL();
    unsigned int createShader(const char* vs, const char* fs);
    unsigned int loadTexture(const std::string& path);
    void computeOrthoMatrix(float* out16, sf::Vector2f camCenter, float width, float height) const;
};