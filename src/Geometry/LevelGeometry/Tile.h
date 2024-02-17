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
    Tile();
    ~Tile() = default;

    virtual void draw(const Shader &shader) const;
    virtual void setup();
    virtual void updateVertex();
    virtual void setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);

protected:
    float textureScale;

    unsigned int VAO, VBO, EBO;
    Texture texture;

};


#endif //CALEBSRENDERER_TILE_H
