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
    explicit TileWrapper(const std::string &n, enum TileWrapperType ty);
    TileWrapper(const TileWrapper &T);
    ~TileWrapper();
    TileWrapper operator= (const TileWrapper &T);

    void setTexture(std::string path);
    void draw(const Shader &s) const;
    void setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);

    glm::vec3 getVert1() const;
    glm::vec3 getVert2() const;
    glm::vec3 getVert3() const;
    glm::vec3 getVert4() const;
    void setVert1(const glm::vec3 &v);
    void setVert2(const glm::vec3 &v);
    void setVert3(const glm::vec3 &v);
    void setVert4(const glm::vec3 &v);

    float getTextureScale() const;
    float getTextureRotation() const;
    glm::vec2 getTexturePosition() const;
    Texture getTexture() const;
    void setTextureScale(const float &s);
    void setTextureRotation(const float &s);
    void setTexturePosition(const glm::vec2 &v);
    void setTexture(const Texture &tex);

    enum TileWrapperType type;

    std::string getName() const;

    bool active;

protected:
    Tile * t;
};


#endif //CALEBSRENDERER_TILEWRAPPER_H
