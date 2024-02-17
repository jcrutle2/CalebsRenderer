//
// Created by Caleb Rutledge on 2/17/24.
//

#ifndef CALEBSRENDERER_TILE_H
#define CALEBSRENDERER_TILE_H

#define TEXTURE_SCALE_DEFAULT 0.25

#include "glm.hpp"
#include "../Models/Shader.h"
#include "../Models/Mesh.h"

namespace TileUtil {

}

class Tile {
public:
    Tile(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);
    ~Tile() = default;

    void draw(const Shader &shader) const;

private:
    glm::vec3 vert1;
    glm::vec3 vert2;
    glm::vec3 vert3;
    glm::vec3 vert4;

    float textureScale;

    unsigned int VAO, VBO, EBO;
    Texture texture;

    void setup();
    void updateVertex();
    float vertex[32];
    unsigned int indices[6];
};


#endif //CALEBSRENDERER_TILE_H
