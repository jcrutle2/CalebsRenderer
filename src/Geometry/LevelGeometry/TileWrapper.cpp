//
// Created by Caleb Rutledge on 2/17/24.
//

#include "TileWrapper.h"
#include "TileTypes/SquareTile.h"

TileWrapper::TileWrapper(const std::string &n, enum TileWrapperType ty) {
    type = ty;
    active = true;

    switch (type) {
        case TILE_SQUARE:
            t = new SquareTile(n, TILE_WRAPPER_V1_DEFAULT, TILE_WRAPPER_V2_DEFAULT, TILE_WRAPPER_V3_DEFAULT, TILE_WRAPPER_V4_DEFAULT);
            break;
        default:
            std::cout << "ERROR: Unable To Initialize Tile Type.";
            break;
    }
}

TileWrapper::TileWrapper(const TileWrapper &T) {
    type = T.type;
    active = T.active;

    switch (type) {
        case TILE_SQUARE:
            t = new SquareTile(T.getName(), T.t->getVert1(), T.t->getVert2(), T.t->getVert3(), T.t->getVert4());
            t->setTexturePosition(T.getTexturePosition());
            t->setTextureRotation(T.getTextureRotation());
            t->setTextureScale(T.getTextureScale());
            t->setTexture(T.getTexture());
            break;
        default:
            std::cout << "ERROR: Unable To Initialize Tile Type.";
            break;
    }
}

TileWrapper TileWrapper::operator= (const TileWrapper &T){
    TileWrapper temp{T.getName(), T.type};
    temp.setTexture(T.getTexture());
    temp.setTextureScale(T.getTextureScale());
    temp.setTextureRotation(T.getTextureRotation());
    temp.setTexturePosition(T.getTexturePosition());

    temp.setVert1(T.getVert1());
    temp.setVert2(T.getVert2());
    temp.setVert3(T.getVert3());
    temp.setVert4(T.getVert4());

    return temp;
}

TileWrapper::~TileWrapper() {
    delete t;
}

void TileWrapper::setTexture(std::string path) {
    t->setTexture(path);
}

void TileWrapper::draw(const Shader &s) const {
    t->draw(s);
}

void TileWrapper::setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    t->setVertexes(v1, v2, v3, v4);
}

std::string TileWrapper::getName() const {
    return t->name;
}

glm::vec3 TileWrapper::getVert1() const {
    return t->getVert1();
}

glm::vec3 TileWrapper::getVert2() const {
    return t->getVert2();
}

glm::vec3 TileWrapper::getVert3() const {
    return t->getVert3();
}

glm::vec3 TileWrapper::getVert4() const {
    return t->getVert4();
}

void TileWrapper::setVert1(const glm::vec3 &v) {
    t->setVert1(v);
}

void TileWrapper::setVert2(const glm::vec3 &v) {
    t->setVert2(v);
}

void TileWrapper::setVert3(const glm::vec3 &v) {
    t->setVert3(v);
}

void TileWrapper::setVert4(const glm::vec3 &v) {
    t->setVert4(v);
}

float TileWrapper::getTextureScale() const {
    return t->getTextureScale();
}
float TileWrapper::getTextureRotation() const {
    return t->getTextureRotation();
}
glm::vec2 TileWrapper::getTexturePosition() const {
    return t->getTexturePosition();
}
Texture TileWrapper::getTexture() const {
    return t->getTexture();
}

void TileWrapper::setTextureScale(const float &s) {
    t->setTextureScale(s);
}
void TileWrapper::setTextureRotation(const float &s) {
    t->setTextureRotation(s);
}
void TileWrapper::setTexturePosition(const glm::vec2 &v) {
    t->setTexturePosition(v);
}
void TileWrapper::setTexture(const Texture &tex) {
    t->setTexture(tex);
}