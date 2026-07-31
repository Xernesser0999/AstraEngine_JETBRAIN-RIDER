#pragma once
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureArrayManager {
public:
    static TextureArrayManager& get();

    void init(int layerSize = 256, int maxLayers = 256);
    int loadTexture(const std::string& path);
    unsigned int getGLTextureId() const { return textureArrayId; }

private:
    unsigned int textureArrayId = 0;
    int layerSize = 256;
    int maxLayers = 256;
    int nextFreeLayer = 0;
    std::unordered_map<std::string, int> pathToLayer;
    
    sf::Image scaleImage(const sf::Image& src, unsigned int newW, unsigned int newH);
};