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
            break;
        default:
            std::cout << "ERROR: Unable To Initialize Tile Type.";
            break;
    }
}

TileWrapper::~TileWrapper() {
    delete t;
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