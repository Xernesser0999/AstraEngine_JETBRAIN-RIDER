#include "TextureArrayManager.h"
#include <iostream>

TextureArrayManager& TextureArrayManager::get() {
    static TextureArrayManager instance;
    return instance;
}

void TextureArrayManager::init(int layerSize_, int maxLayers_) {
    layerSize = layerSize_;
    maxLayers = maxLayers_;

    glGenTextures(1, &textureArrayId);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayId);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, layerSize, layerSize, maxLayers,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int TextureArrayManager::loadTexture(const std::string& path) {
    auto it = pathToLayer.find(path);
    if (it != pathToLayer.end()) return it->second;

    if (nextFreeLayer >= maxLayers) {
        std::cerr << "TextureArrayManager: plus de layers disponibles !" << std::endl;
        return -1;
    }

    sf::Image image;
    if (!image.loadFromFile(path)) {
        std::cerr << "Echec du chargement de la texture : " << path << std::endl;
        return -1;
    }

    image = scaleImage(image, layerSize, layerSize);

    std::cout << "Texture chargee : " << path << " -> layer " << (nextFreeLayer - 1) << " taille source " << image.getSize().x << "x" << image.getSize().y << std::endl;
    
    int layer = nextFreeLayer++;
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayId);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer,
                     layerSize, layerSize, 1,
                     GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    pathToLayer[path] = layer;
    return layer;
}

sf::Image TextureArrayManager::scaleImage(const sf::Image& src, unsigned int newW, unsigned int newH) {
    sf::Image dst(sf::Vector2u(newW, newH));
    auto srcSize = src.getSize();

    for (unsigned int y = 0; y < newH; y++) {
        for (unsigned int x = 0; x < newW; x++) {
            unsigned int srcX = x * srcSize.x / newW;
            unsigned int srcY = y * srcSize.y / newH;
            dst.setPixel({x, y}, src.getPixel({srcX, srcY}));
        }
    }
    return dst;
}