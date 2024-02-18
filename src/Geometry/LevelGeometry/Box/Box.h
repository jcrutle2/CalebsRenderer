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
#define BOX_SCALE_DEFAULT (glm::vec3(1.0f))

class Box {
public:
    explicit Box(glm::vec3 pos);
    ~Box() = default;

    void draw(const Shader &s) const;

    // getter methods
    glm::vec3 getPosition() const;
    glm::vec3 getRotationAxis() const;
    float getRotation() const;
    glm::vec3 getScale() const;

    // setter methods
    void setPosition(glm::vec3 pos);
    void setRotationAxis(glm::vec3 rot);
    void setRotation(float r);
    void setScale(glm::vec3 s);
    void setBoxVertices(glm::vec3 b0, glm::vec3 b1, glm::vec3 b2, glm::vec3 b3, glm::vec3 b4, glm::vec3 b5, glm::vec3 b6, glm::vec3 b7);

    // tiling
    std::vector<TileWrapper>& getTileList();
    void pushBack(enum TileWrapperType type);

private:
    // model location
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotation;
    glm::vec3 scale;

    // local locations
    glm::vec3 boxVertices[8];
    std::vector<TileWrapper> tiles;
    void setupCube(glm::vec3 b0, glm::vec3 b1, glm::vec3 b2, glm::vec3 b3, glm::vec3 b4, glm::vec3 b5, glm::vec3 b6, glm::vec3 b7);
};


#endif //CALEBSRENDERER_BOX_H
