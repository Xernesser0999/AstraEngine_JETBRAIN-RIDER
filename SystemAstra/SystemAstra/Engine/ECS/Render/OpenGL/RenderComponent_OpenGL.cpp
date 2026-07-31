#include "RenderComponent_OpenGL.h"
#include "TextureArrayManager.h"
#include "RenderSystem.h"
#include "../../Object.h"

RenderComponent_OpenGL::RenderComponent_OpenGL(Object* _owner, const std::string& texturePath)
    : Component(_owner)
{
    textureLayer = TextureArrayManager::get().loadTexture(texturePath);
    position = _owner->getPosition();
    size = _owner->getSize();
    RenderSystem::get().registerComponent(this);
}

RenderComponent_OpenGL::~RenderComponent_OpenGL() {
    RenderSystem::get().unregisterComponent(this);
}

void RenderComponent_OpenGL::setTexture(const std::string& texturePath) {
    textureLayer = TextureArrayManager::get().loadTexture(texturePath);
}

void RenderComponent_OpenGL::update(float dt) {

}