//
// Created by Caleb Rutledge on 2/17/24.
//

#ifndef CALEBSRENDERER_SQUARETILE_H
#define CALEBSRENDERER_SQUARETILE_H

#include "Tile.h"

class SquareTile : public Tile {
public:
    SquareTile(const std::string &n, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);
    SquareTile(const SquareTile &S);
    ~SquareTile() = default;

    void setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) override;
    glm::vec3 getVert1() const override;
    glm::vec3 getVert2() const override;
    glm::vec3 getVert3() const override;
    glm::vec3 getVert4() const override;

private:
    glm::vec3 vert1;
    glm::vec3 vert2;
    glm::vec3 vert3;
    glm::vec3 vert4;

    float vertex[32];
    unsigned int indices[6];

    void updateVertex() override;
    void setup() override;
    void draw(const Shader &shader) const override;

};


#endif //CALEBSRENDERER_SQUARETILE_H
