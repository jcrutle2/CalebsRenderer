//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Tile.h"

Tile::Tile() {
    textureScale = TEXTURE_SCALE_DEFAULT;
    newTexture(texture, "Assets/Textures/error.png", "png");
}

void Tile::updateVertex() {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

void Tile::setup() {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

void Tile::draw(const Shader &shader) const {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

void Tile::setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

glm::vec3 Tile::getVert1() const {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

glm::vec3 Tile::getVert2() const {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

glm::vec3 Tile::getVert3() const {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}

glm::vec3 Tile::getVert4() const {
    std::cout << "ERROR: INVALID TILE TYPE";
    exit(1);
}