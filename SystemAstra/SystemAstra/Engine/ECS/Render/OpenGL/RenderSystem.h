#pragma once
#include <glad/glad.h>
#include <vector>

class RenderComponent_OpenGL;

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
    void registerComponent(RenderComponent_OpenGL* c);
    void unregisterComponent(RenderComponent_OpenGL* c);
    void renderAll();

private:
    unsigned int vao = 0, quadVBO = 0, instanceVBO = 0, shader = 0;
    std::vector<RenderComponent_OpenGL*> components;

    unsigned int createShader(const char* vs, const char* fs);
};