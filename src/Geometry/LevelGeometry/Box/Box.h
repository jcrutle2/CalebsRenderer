//
// Created by Caleb Rutledge on 2/17/24.
//

#ifndef CALEBSRENDERER_BOX_H
#define CALEBSRENDERER_BOX_H

#include <glm.hpp>
#include "../TileWrapper.h"

#define BOX_VERTEX_0_DEFAULT (glm::vec3(8.0f, 8.0f, -8.0f))
#define BOX_VERTEX_1_DEFAULT (glm::vec3(8.0f, 8.0f, 8.0f))
#define BOX_VERTEX_2_DEFAULT (glm::vec3(-8.0f, 8.0f, 8.0f))
#define BOX_VERTEX_3_DEFAULT (glm::vec3(-8.0f, 8.0f, -8.0f))
#define BOX_VERTEX_4_DEFAULT (glm::vec3(8.0f, 0.0f, -8.0f))
#define BOX_VERTEX_5_DEFAULT (glm::vec3(-8.0f, 0.0f, -8.0f))
#define BOX_VERTEX_6_DEFAULT (glm::vec3(-8.0f, 0.0f, 8.0f))
#define BOX_VERTEX_7_DEFAULT (glm::vec3(8.0f, 0.0f, 8.0f))
#define BOX_ROTATION_AXIS_DEFAULT (glm::vec3(0.0f, 1.0f, 0.0f))
#define BOX_ROTATION_DEFAULT (0.0f)
#define BOX_SCALE_DEFAULT (glm::vec3(1.0f, 1.0f, 1.0f))
#define NEW_GEOMETRY_0_DEFAULT (glm::vec3(1.0f, 1.0f, 0.0f))
#define NEW_GEOMETRY_1_DEFAULT (glm::vec3(-1.0f, 1.0f, 0.0f))
#define NEW_GEOMETRY_2_DEFAULT (glm::vec3(-1.0f, -1.0f, 0.0f))
#define NEW_GEOMETRY_3_DEFAULT (glm::vec3(1.0f, -1.0f, 0.0f))

class Box {
public:
    explicit Box(const std::string &n, const glm::vec3 &pos);
    ~Box() = default;

    void draw(const Shader &s) const;

    // getter methods
    glm::vec3 getPosition() const;
    glm::vec3 getRotationAxis() const;
    float getRotation() const;
    glm::vec3 getScale() const;
    glm::vec3 getV0() const;
    glm::vec3 getV1() const;
    glm::vec3 getV2() const;
    glm::vec3 getV3() const;
    glm::vec3 getV4() const;
    glm::vec3 getV5() const;
    glm::vec3 getV6() const;
    glm::vec3 getV7() const;
    bool getActive(unsigned int side);
    glm::vec3 getTileVert1(const unsigned int &n) const;
    glm::vec3 getTileVert2(const unsigned int &n) const;
    glm::vec3 getTileVert3(const unsigned int &n) const;
    glm::vec3 getTileVert4(const unsigned int &n) const;
    float getTextureRotation(const unsigned int &n) const;
    float getTextureScale(const unsigned int &n) const;
    glm::vec2 getTexturePosition(const unsigned int &n) const;


    // setter methods
    void setPosition(glm::vec3 pos);
    void setRotationAxis(glm::vec3 rot);
    void setRotation(float r);
    void setScale(glm::vec3 s);
    void setV0(const glm::vec3 &v);
    void setV1(const glm::vec3 &v);
    void setV2(const glm::vec3 &v);
    void setV3(const glm::vec3 &v);
    void setV4(const glm::vec3 &v);
    void setV5(const glm::vec3 &v);
    void setV6(const glm::vec3 &v);
    void setV7(const glm::vec3 &v);
    void toggleActive(unsigned int side);
    void setBoxTextures(std::string path);
    void setAllTextures(std::string path);
    void setTexture(const unsigned int &n, const std::string &path);
    void setTileVert1(const unsigned int &n, const glm::vec3 &v);
    void setTileVert2(const unsigned int &n, const glm::vec3 &v);
    void setTileVert3(const unsigned int &n, const glm::vec3 &v);
    void setTileVert4(const unsigned int &n, const glm::vec3 &v);
    void setAllTextureScale(const float &r);
    void setAllTextureRotation(const float &r);
    void setAllTexturePosition(const glm::vec2 &v);
    void setBoxTextureScale(const float &r);
    void setBoxTextureRotation(const float &r);
    void setBoxTexturePosition(const glm::vec2 &v);
    void setTextureScale(const unsigned int &n, const float &s);
    void setTextureRotation(const unsigned int &n, const float &r);
    void setTexturePosition(const unsigned int &n, const glm::vec2 &v);

    // tiling
    std::vector<TileWrapper>& getTileList();
    void pushBack(enum TileWrapperType type);

    std::string name;

private:
    // model location
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotation;
    glm::vec3 scale;

    // local locations
    glm::vec3 boxVertices[8];
    std::vector<TileWrapper> tiles;
    void setupCube();
    void editCube(glm::vec3 b0, glm::vec3 b1, glm::vec3 b2, glm::vec3 b3, glm::vec3 b4, glm::vec3 b5, glm::vec3 b6, glm::vec3 b7);
};


#endif //CALEBSRENDERER_BOX_H
