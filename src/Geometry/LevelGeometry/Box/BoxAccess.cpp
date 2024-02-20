//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Box.h"

std::string Box::getName() const {
    return name;
}

glm::vec3 Box::getPosition() const {
    return position;
}

glm::vec3 Box::getRotationAxis() const {
    return rotationAxis;
}

float Box::getRotation() const {
    return rotation;
}

glm::vec3 Box::getScale() const {
    return scale;
}

glm::vec3 Box::getV0() const {
    return boxVertices[0];
}
glm::vec3 Box::getV1() const {
    return boxVertices[1];
}
glm::vec3 Box::getV2() const {
    return boxVertices[2];
}
glm::vec3 Box::getV3() const {
    return boxVertices[3];
}
glm::vec3 Box::getV4() const {
    return boxVertices[4];
}
glm::vec3 Box::getV5() const {
    return boxVertices[5];
}
glm::vec3 Box::getV6() const {
    return boxVertices[6];
}
glm::vec3 Box::getV7() const {
    return boxVertices[7];
}

glm::vec3 Box::getTileVert1(const unsigned int &n) const {
    return tiles[n].getVert1();
}
glm::vec3 Box::getTileVert2(const unsigned int &n) const {
    return tiles[n].getVert2();
}
glm::vec3 Box::getTileVert3(const unsigned int &n) const {
    return tiles[n].getVert3();
}
glm::vec3 Box::getTileVert4(const unsigned int &n) const {
    return tiles[n].getVert4();
}

float Box::getTextureScale(const unsigned int &n) const {
    return tiles[n].getTextureScale();
}
float Box::getTextureRotation(const unsigned int &n) const {
    return tiles[n].getTextureRotation();
}
glm::vec2 Box::getTexturePosition(const unsigned int &n) const {
    return tiles[n].getTexturePosition();
}



void Box::setName(const std::string &n) {
    name = n;
}

void Box::setPosition(glm::vec3 pos) {
    position = pos;
}

void Box::setRotationAxis(glm::vec3 rot) {
    rotationAxis = rot;
}

void Box::setRotation(float r) {
    rotation = r;
}

void Box::setScale(glm::vec3 s) {
    scale = s;
}

void Box::setV0(const glm::vec3 &v) {
    boxVertices[0] = v;
    setupCube();
}
void Box::setV1(const glm::vec3 &v) {
    boxVertices[1] = v;
    setupCube();
}
void Box::setV2(const glm::vec3 &v) {
    boxVertices[2] = v;
    setupCube();
}
void Box::setV3(const glm::vec3 &v) {
    boxVertices[3] = v;
    setupCube();
}
void Box::setV4(const glm::vec3 &v) {
    boxVertices[4] = v;
    setupCube();
}
void Box::setV5(const glm::vec3 &v) {
    boxVertices[5] = v;
    setupCube();
}
void Box::setV6(const glm::vec3 &v) {
    boxVertices[6] = v;
    setupCube();
}
void Box::setV7(const glm::vec3 &v) {
    boxVertices[7] = v;
    setupCube();
}

void Box::setTexture(const unsigned int &n, const std::string &path) {
    tiles[n].setTexture(path);
}
void Box::setAllTextures(std::string path) {
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i].setTexture(path);
    }
}
void Box::setBoxTextures(std::string path) {
    for (int i = 0; i < 6; i++) {
        tiles[i].setTexture(path);
    }
}

void Box::setTileVert1(const unsigned int &n, const glm::vec3 &v) {
    tiles[n].setVert1(v);
}
void Box::setTileVert2(const unsigned int &n, const glm::vec3 &v) {
    tiles[n].setVert2(v);
}
void Box::setTileVert3(const unsigned int &n, const glm::vec3 &v) {
    tiles[n].setVert3(v);
}
void Box::setTileVert4(const unsigned int &n, const glm::vec3 &v) {
    tiles[n].setVert4(v);
}

void Box::setAllTextureScale(const float &r) {
    for (auto &tile : tiles)
        tile.setTextureScale(r);
}
void Box::setAllTextureRotation(const float &r) {
    for (auto &tile : tiles)
        tile.setTextureRotation(r);
}
void Box::setAllTexturePosition(const glm::vec2 &v) {
    for (auto &tile : tiles)
        tile.setTexturePosition(v);
}
void Box::setBoxTextureScale(const float &r) {
    for (int i = 0; i < 6; i++)
        tiles[i].setTextureScale(r);
}
void Box::setBoxTextureRotation(const float &r) {
    for (int i = 0; i < 6; i++)
        tiles[i].setTextureRotation(r);
}
void Box::setBoxTexturePosition(const glm::vec2 &v) {
    for (int i = 0; i < 6; i++)
        tiles[i].setTexturePosition(v);
}
void Box::setTextureScale(const unsigned int &n, const float &r) {
    tiles[n].setTextureScale(r);
}
void Box::setTextureRotation(const unsigned int &n, const float &r) {
    tiles[n].setTextureRotation(r);
}
void Box::setTexturePosition(const unsigned int &n, const glm::vec2 &v) {
    tiles[n].setTexturePosition(v);
}