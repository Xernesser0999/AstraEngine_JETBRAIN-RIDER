#include "RenderSystem.h"
#include "RenderComponent_OpenGL.h"
#include "TextureArrayManager.h"
#include "../../../Main/GameEngine.h"
#include <algorithm>
#include <iostream>

RenderSystem& RenderSystem::get() {
    static RenderSystem instance;
    return instance;
}

void RenderSystem::init() {
    float quad[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO du quad (partagé par toutes les instances)
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBO des instances (rempli chaque frame)
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    glEnableVertexAttribArray(1); // position
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, posX));
    glVertexAttribDivisor(1, 1);

    glEnableVertexAttribArray(2); // size
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, sizeX));
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(3); // rotation
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, rotation));
    glVertexAttribDivisor(3, 1);

    glEnableVertexAttribArray(4); // layer
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, layer));
    glVertexAttribDivisor(4, 1);

    const char* vs = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 iPos;
        layout(location = 2) in vec2 iSize;
        layout(location = 3) in float iRotation;
        layout(location = 4) in float iLayer;

        uniform mat4 projection;
        out vec2 vUV;
        flat out float vLayer;

        void main() {
            float rad = radians(iRotation);
            mat2 rot = mat2(cos(rad), -sin(rad), sin(rad), cos(rad));
            vec2 world = iPos + rot * (aPos * iSize);
            gl_Position = projection * vec4(world, 0.0, 1.0);
            vUV = aPos + 0.5;
            vLayer = iLayer;
        }
    )";

    const char* fs = R"(
        #version 330 core
        in vec2 vUV;
        flat in float vLayer;
        out vec4 FragColor;
        uniform sampler2DArray texArray;

        void main() {
            FragColor = texture(texArray, vec3(vUV, vLayer));
        }
    )";

    shader = createShader(vs, fs);
}

unsigned int RenderSystem::createShader(const char* vs, const char* fs) {
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vs, nullptr);
    glCompileShader(vertex);

    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "Erreur compilation vertex shader:\n" << infoLog << std::endl;
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "Erreur compilation fragment shader:\n" << infoLog << std::endl;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Erreur link shader:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    
    return program;
}

void RenderSystem::registerComponent(RenderComponent_OpenGL* c) {
    components.push_back(c);
}

void RenderSystem::unregisterComponent(RenderComponent_OpenGL* c) {
    components.erase(std::remove(components.begin(), components.end(), c), components.end());
}

void RenderSystem::renderAll() {
    if (components.empty()) return;

    std::vector<InstanceData> instances;
    instances.reserve(components.size());
    for (auto* c : components) {
        instances.push_back({
            c->getPosition().x, c->getPosition().y,
            c->getSize().x, c->getSize().y,
            c->getRotation(), (float)c->getTextureLayer()
        });
    }

    glUseProgram(shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, TextureArrayManager::get().getGLTextureId());
    glUniform1i(glGetUniformLocation(shader, "texArray"), 0);

    auto winSize = GameEngine::getWindow()->getSize();
    sf::Vector2f camCenter = GameEngine::getWindow()->getView().getCenter();
    float left   = camCenter.x - winSize.x / 2.0f;
    float right  = camCenter.x + winSize.x / 2.0f;
    float top    = camCenter.y - winSize.y / 2.0f;
    float bottom = camCenter.y + winSize.y / 2.0f;
    float near = -1.0f, far = 1.0f;

    float proj[16] = { 0 };
    proj[0]  = 2.0f / (right - left);
    proj[5]  = 2.0f / (top - bottom);
    proj[10] = -2.0f / (far - near);
    proj[12] = -(right + left) / (right - left);
    proj[13] = -(top + bottom) / (top - bottom);
    proj[14] = -(far + near) / (far - near);
    proj[15] = 1.0f;

    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, proj);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceData),
                 instances.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, (GLsizei)instances.size());
}
