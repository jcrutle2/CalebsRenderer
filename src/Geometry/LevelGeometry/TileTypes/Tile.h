//
// Created by Caleb Rutledge on 2/17/24.
//

#ifndef CALEBSRENDERER_TILE_H
#define CALEBSRENDERER_TILE_H

#define TEXTURE_SCALE_DEFAULT 4.0f
#define TEXTURE_ROTATION_DEFAULT 0.0f
#define TEXTURE_POSITION_DEFAULT (glm::vec2(0.0f, 0.0f))

#include "glm.hpp"
#include "../../Models/Shader.h"
#include "../../Models/Mesh.h"

namespace TileUtil {

}

class Tile {
public:
    Tile();
    Tile(const std::string &n);
    ~Tile() = default;

    std::string name;

    void setTexture(const std::string &path);

    virtual void draw(const Shader &shader) const;
    virtual void updateVertex();
    virtual void setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);
    virtual glm::vec3 getVert1() const;
    virtual glm::vec3 getVert2() const;
    virtual glm::vec3 getVert3() const;
    virtual glm::vec3 getVert4() const;
    virtual void setVert1(const glm::vec3 &v);
    virtual void setVert2(const glm::vec3 &v);
    virtual void setVert3(const glm::vec3 &v);
    virtual void setVert4(const glm::vec3 &v);

    float getTextureScale() const;
    float getTextureRotation() const;
    glm::vec2 getTexturePosition() const;
    Texture getTexture() const;
    void setTextureScale(const float &s);
    void setTextureRotation(const float &r);
    void setTexturePosition(const glm::vec2 &v);
    void setTexture(const Texture &t);



protected:
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive &ar);

    float textureScale;
    float textureRotation;
    glm::vec2 texturePosition;

    unsigned int VAO, VBO, EBO;
    Texture texture;
};


#endif //CALEBSRENDERER_TILE_H
