#pragma once
#include <glad/glad.h>
#include <vector>

class RenderComponent;

struct InstanceData {
    float posX, posY;
    float sizeX, sizeY;
    float rotation;
    float layer;
};

class RenderSystem {
public:
    static RenderSystem& get();

    void init();
    void registerComponent(RenderComponent* c);
    void unregisterComponent(RenderComponent* c);
    void renderAll();

private:
    unsigned int vao = 0, quadVBO = 0, instanceVBO = 0, shader = 0;
    std::vector<RenderComponent*> components;

    unsigned int createShader(const char* vs, const char* fs);
};