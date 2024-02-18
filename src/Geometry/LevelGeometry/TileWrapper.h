//
// Created by Caleb Rutledge on 2/17/24.
//

#ifndef CALEBSRENDERER_TILEWRAPPER_H
#define CALEBSRENDERER_TILEWRAPPER_H

#include "../Models/Shader.h"
#include "TileTypes/SquareTile.h"

#define TILE_WRAPPER_V1_DEFAULT (glm::vec3(1.0f, 0.0f, -1.0f))
#define TILE_WRAPPER_V2_DEFAULT (glm::vec3(-1.0f, 0.0f, -1.0f))
#define TILE_WRAPPER_V3_DEFAULT (glm::vec3(-1.0f, 0.0f, 1.0f))
#define TILE_WRAPPER_V4_DEFAULT (glm::vec3(1.0f, 0.0f, 1.0f))

enum TileWrapperType {
    TILE_SQUARE
};

class TileWrapper {
public:
    explicit TileWrapper(enum TileWrapperType ty);
    TileWrapper(const TileWrapper &T);
    ~TileWrapper();
    TileWrapper& operator= (const TileWrapper &T);

    void draw(const Shader &s) const;
    void setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);

    enum TileWrapperType type;

    bool active;

protected:
    Tile * t;
};


#endif //CALEBSRENDERER_TILEWRAPPER_H