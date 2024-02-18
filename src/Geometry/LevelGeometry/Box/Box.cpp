//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Box.h"

Box::Box(glm::vec3 pos) {
    tiles.emplace_back(TILE_SQUARE);
    tiles.emplace_back(TILE_SQUARE);
    tiles.emplace_back(TILE_SQUARE);
    tiles.emplace_back(TILE_SQUARE);
    tiles.emplace_back(TILE_SQUARE);
    tiles.emplace_back(TILE_SQUARE);

    position = pos;
    rotationAxis = BOX_ROTATION_AXIS_DEFAULT;
    rotation = BOX_ROTATION_DEFAULT;
    scale = BOX_SCALE_DEFAULT;

    setupCube(BOX_VERTEX_0_DEFAULT, BOX_VERTEX_1_DEFAULT,
              BOX_VERTEX_2_DEFAULT, BOX_VERTEX_3_DEFAULT,
              BOX_VERTEX_4_DEFAULT, BOX_VERTEX_5_DEFAULT,
              BOX_VERTEX_6_DEFAULT, BOX_VERTEX_7_DEFAULT);
}

void Box::setupCube(glm::vec3 b0, glm::vec3 b1, glm::vec3 b2, glm::vec3 b3, glm::vec3 b4, glm::vec3 b5, glm::vec3 b6,
                    glm::vec3 b7) {
    boxVertices[0] = b0;
    boxVertices[1] = b1;
    boxVertices[2] = b2;
    boxVertices[3] = b3;
    boxVertices[4] = b4;
    boxVertices[5] = b5;
    boxVertices[6] = b6;
    boxVertices[7] = b7;

    // front + back cubes
    tiles[0].setVertexes(b1, b7, b6, b2);
    tiles[1].setVertexes(b3, b5, b4, b0);
    // left + right cubes
    tiles[2].setVertexes(b2, b6, b5, b3);
    tiles[3].setVertexes(b0, b4, b7, b1);
    // top + bottom cubes
    tiles[4].setVertexes(b0, b1, b2, b3);
    tiles[5].setVertexes(b4, b5, b6, b7);
}

void Box::draw(const Shader &s) const {
    for (auto const &t : tiles) {
        if (t.active)
            t.draw(s);
    }
}