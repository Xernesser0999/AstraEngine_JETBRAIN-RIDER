#include "RenderComponent.h"
#include "../../Main/GameEngine.h"
#include <iostream>

RenderComponent::RenderComponent(Object* owner, const std::string& texturePath)
    : Component(owner)
{
    initGL();
    texture = loadTexture(texturePath);
    
    setPosition(owner->getPosition());
}

RenderComponent::~RenderComponent() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
}

unsigned int RenderComponent::loadTexture(const std::string& path) {
    sf::Image image;
    if (!image.loadFromFile(path)) {
        std::cerr << "Echec du chargement de la texture : " << path << std::endl;
        return 0;
    }


    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto size = image.getSize();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    return texId;
}

void RenderComponent::initGL() {
    // Quad avec position (x,y) + UV (u,v)
    float vertices[] = {
        // pos          // uv
        -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,   0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const char* vs = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aUV;

        uniform mat4 model;
        uniform mat4 projection;

        out vec2 vUV;

        void main() {
            vUV = aUV;
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fs = R"(
        #version 330 core
        in vec2 vUV;
        out vec4 FragColor;

        uniform sampler2D tex;

        void main() {
            FragColor = texture(tex, vUV);
        }
    )";

    shader = createShader(vs, fs);
}

void RenderComponent::computeOrthoMatrix(float* out16, sf::Vector2f camCenter, float width, float height) const {
    float left   = camCenter.x - width / 2.0f;
    float right  = camCenter.x + width / 2.0f;
    float top    = camCenter.y - height / 2.0f;
    float bottom = camCenter.y + height / 2.0f;
    float near = -1.0f, far = 1.0f;

    for (int i = 0; i < 16; i++) out16[i] = 0.0f;

    out16[0]  = 2.0f / (right - left);
    out16[5]  = 2.0f / (top - bottom);
    out16[10] = -2.0f / (far - near);
    out16[12] = -(right + left) / (right - left);
    out16[13] = -(top + bottom) / (top - bottom);
    out16[14] = -(far + near) / (far - near);
    out16[15] = 1.0f;
}

unsigned int RenderComponent::createShader(const char* vs, const char* fs) {
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vs, nullptr);
    glCompileShader(vertex);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, nullptr);
    glCompileShader(fragment);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void RenderComponent::update(float dt) {
    // Rien pour l'instant
}

void RenderComponent::render() {
    glUseProgram(shader);

    // Transform du sprite (position/taille/rotation en pixels)
    sf::Transform transform;
    transform.translate(position);
    transform.rotate(sf::degrees(rotation));
    transform.scale(size);

    int modelLoc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, transform.getMatrix());

    // Projection : convertit les pixels en NDC selon la taille de la fenêtre
    auto winSize = GameEngine::getWindow()->getSize();
    sf::Vector2f camCenter = GameEngine::getWindow()->getView().getCenter(); // ← la vraie astuce
    float projMatrix[16];
    computeOrthoMatrix(projMatrix, camCenter, (float)winSize.x, (float)winSize.y);

    int projLoc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "tex"), 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void RenderComponent::setTexture(std::string texturePath) {
    texture = loadTexture(texturePath);
}

void RenderComponent::setPosition(const sf::Vector2f& pos) { position = pos; }
void RenderComponent::setSize(const sf::Vector2f& newSize) { size = newSize; }
void RenderComponent::setRotation(float degrees) { rotation = degrees; }
