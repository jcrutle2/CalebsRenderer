//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Tile.h"

Tile::Tile() {
    name = "";
    textureScale = TEXTURE_SCALE_DEFAULT;
    textureRotation = TEXTURE_ROTATION_DEFAULT;
    texturePosition = TEXTURE_POSITION_DEFAULT;
    newTexture(texture, "Assets/Textures/brick/main.png", "png");
}

Tile::Tile(const std::string &n) {
    name = n;
    textureScale = TEXTURE_SCALE_DEFAULT;
    textureRotation = TEXTURE_ROTATION_DEFAULT;
    texturePosition = TEXTURE_POSITION_DEFAULT;
    newTexture(texture, "Assets/Textures/brick/main.png", "png");
}

void Tile::setTexture(const std::string &path) {
    newTexture(texture, path.c_str(), TextureGlobals::fileExtension(path).c_str());
}
void Tile::setTexture(const Texture &t) {
    texture = t;
}

void Tile::updateVertex() {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::draw(const Shader &shader) const {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

glm::vec3 Tile::getVert1() const {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

glm::vec3 Tile::getVert2() const {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

glm::vec3 Tile::getVert3() const {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

glm::vec3 Tile::getVert4() const {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::setVert1(const glm::vec3 &v) {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::setVert2(const glm::vec3 &v) {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::setVert3(const glm::vec3 &v) {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

void Tile::setVert4(const glm::vec3 &v) {
    throw std::invalid_argument("ERROR: INVALID TILE TYPE");
}

float Tile::getTextureScale() const {
    return textureScale;
}

float Tile::getTextureRotation() const {
    return textureRotation;
}

glm::vec2 Tile::getTexturePosition() const {
    return texturePosition;
}

Texture Tile::getTexture() const {
    return texture;
}

void Tile::setTextureScale(const float &s) {
    textureScale = s;
    updateVertex();
}

void Tile::setTextureRotation(const float &r) {
    textureRotation = r;
    updateVertex();
}

void Tile::setTexturePosition(const glm::vec2 &v) {
    texturePosition = v;
    updateVertex();
}


