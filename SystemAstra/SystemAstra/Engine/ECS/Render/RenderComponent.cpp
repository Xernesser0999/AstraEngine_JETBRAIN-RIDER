#include "RenderComponent.h"
#include "TextureArrayManager.h"
#include "RenderSystem.h"
#include "../Object.h"

RenderComponent::RenderComponent(Object* _owner, const std::string& texturePath)
    : Component(_owner)
{
    textureLayer = TextureArrayManager::get().loadTexture(texturePath);
    position = _owner->getPosition();
    size = _owner->getSize();
    RenderSystem::get().registerComponent(this);
}

RenderComponent::~RenderComponent() {
    RenderSystem::get().unregisterComponent(this);
}

void RenderComponent::setTexture(const std::string& texturePath) {
    textureLayer = TextureArrayManager::get().loadTexture(texturePath);
}

void RenderComponent::update(float dt) {

}