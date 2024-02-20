//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Box.h"

Box::Box(const std::string &n, const glm::vec3 &pos) {
    name = n;

    tiles.emplace_back("Front", TILE_SQUARE);
    tiles.emplace_back("Back", TILE_SQUARE);
    tiles.emplace_back("Left", TILE_SQUARE);
    tiles.emplace_back("Right", TILE_SQUARE);
    tiles.emplace_back("Top", TILE_SQUARE);
    tiles.emplace_back("Bottom", TILE_SQUARE);

    position = pos;
    rotationAxis = BOX_ROTATION_AXIS_DEFAULT;
    rotation = BOX_ROTATION_DEFAULT;
    scale = BOX_SCALE_DEFAULT;

    editCube(BOX_VERTEX_0_DEFAULT, BOX_VERTEX_1_DEFAULT,
             BOX_VERTEX_2_DEFAULT, BOX_VERTEX_3_DEFAULT,
             BOX_VERTEX_4_DEFAULT, BOX_VERTEX_5_DEFAULT,
             BOX_VERTEX_6_DEFAULT, BOX_VERTEX_7_DEFAULT);
}

void Box::editCube(glm::vec3 b0, glm::vec3 b1, glm::vec3 b2, glm::vec3 b3, glm::vec3 b4, glm::vec3 b5, glm::vec3 b6,
                   glm::vec3 b7) {
    boxVertices[0] = b0;
    boxVertices[1] = b1;
    boxVertices[2] = b2;
    boxVertices[3] = b3;
    boxVertices[4] = b4;
    boxVertices[5] = b5;
    boxVertices[6] = b6;
    boxVertices[7] = b7;

    setupCube();
}

void Box::setupCube() {
    // front + back cubes
    tiles[0].setVertexes(boxVertices[1], boxVertices[7], boxVertices[6], boxVertices[2]);
    tiles[1].setVertexes(boxVertices[3], boxVertices[5], boxVertices[4], boxVertices[0]);
    // left + right cubes
    tiles[2].setVertexes(boxVertices[2], boxVertices[6], boxVertices[5], boxVertices[3]);
    tiles[3].setVertexes(boxVertices[0], boxVertices[4], boxVertices[7], boxVertices[1]);
    // top + bottom cubes
    tiles[4].setVertexes(boxVertices[0], boxVertices[1], boxVertices[2], boxVertices[3]);
    tiles[5].setVertexes(boxVertices[7], boxVertices[4], boxVertices[5], boxVertices[6]);
}

void Box::draw(const Shader &s) const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::rotate(model, (rotation / 360.0f) * (static_cast<float>(2.0f*M_PI_2)), rotationAxis);
    model = glm::scale(model, scale);

    s.setModel(model);
    for (auto const &t : tiles) {
        if (t.active)
            t.draw(s);
    }
}

std::vector<TileWrapper>& Box::getTileList() {
    return tiles;
}

void Box::toggleActive(unsigned int side) {
    if (side < tiles.size()) {
        tiles[side].active = !tiles[side].active;
    }
}

void Box::setActive(unsigned int side, const bool &setter) {
    if (side < tiles.size()) {
        tiles[side].active = setter;
    }
}

bool Box::getActive(unsigned int side) {
    if (side < tiles.size()) {
        return tiles[side].active;
    }
    return false;
}

void Box::pushBack(enum TileWrapperType type) {
    std::string tileName = "Side " + std::to_string(tiles.size() + 1);
    tiles.emplace_back(tileName, type);
}