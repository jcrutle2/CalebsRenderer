//
// Created by Caleb Rutledge on 2/17/24.
//

#include "SquareTile.h"

SquareTile::SquareTile(const std::string &n, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) : Tile(n) {
    vert1 = v1;
    vert2 = v2;
    vert3 = v3;
    vert4 = v4;

    updateVertex();
}

SquareTile::SquareTile(const SquareTile &S) : Tile(S.name){
    vert1 = S.vert1;
    vert2 = S.vert2;
    vert3 = S.vert3;
    vert4 = S.vert4;

    updateVertex();
}

void SquareTile::updateVertex() {
    // calculate normal vectors
    glm::vec3 norm1 = glm::normalize(glm::cross(vert2 - vert1, vert4 - vert1));
    glm::vec3 norm2 = glm::normalize(glm::cross(vert3 - vert2, vert1 - vert2));
    glm::vec3 norm3 = glm::normalize(glm::cross(vert4 - vert3, vert2 - vert3));
    glm::vec3 norm4 = glm::normalize(glm::cross(vert1 - vert4, vert3 - vert4));

    // Used to Calculate Mapping Points
    glm::vec3 rHat = glm::normalize(vert4 - vert3);
    float rMag = glm::length(vert4 - vert3);
    glm::vec3 vecTwoThree = vert2 - vert3;
    glm::vec3 vecOneThree = vert1 - vert3;

    // Texture Mapping Coordinates
    glm::vec4 coordsOne = glm::vec4(
            1.0f - (glm::length(glm::vec3((vecOneThree) - (rHat * glm::dot(rHat, vecOneThree)))) / textureScale),
            1.0f - (glm::length(rHat * glm::dot(rHat, vecOneThree)) / textureScale),
            0.0f,
            0.0f
    );
    glm::vec4 coordsTwo = glm::vec4(
            1.0f - (glm::length((vecTwoThree) - (rHat * glm::dot(rHat, vecTwoThree))) / textureScale),
            1.0f - (glm::length(rHat * glm::dot(rHat, vecTwoThree)) / textureScale),
            0.0f,
            0.0f
    );
    glm::vec4 coordsThree = glm::vec4(
            1.0f,
            1.0f,
            0.0f,
            0.0f
    );
    glm::vec4 coordsFour = glm::vec4(
            1.0f,
            vertex[31] = 1.0f - (rMag / textureScale),
            0.0f,
            0.0f
    );

    // Rotate Texture Coordinates
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (textureRotation / 360.0f) * 2 * (float) M_PI, glm::vec3(0.0f, 0.0f, 1.0f));
    coordsOne = rotation * coordsOne;
    coordsTwo = rotation * coordsTwo;
    coordsThree = rotation * coordsThree;
    coordsFour = rotation * coordsFour;

    // Translate Texture Coordinates
    glm::vec4 translation = glm::vec4(texturePosition, 0.0f, 0.0f);
    coordsOne += translation;
    coordsTwo += translation;
    coordsThree += translation;
    coordsFour += translation;

    // Assign Calculated Values to Vertex Array
    vertex[0] = vert1.x;
    vertex[1] = vert1.y;
    vertex[2] = vert1.z;
    vertex[3] = norm1.x;
    vertex[4] = norm1.y;
    vertex[5] = norm1.z;
    vertex[6] = coordsOne.x;
    vertex[7] = coordsOne.y;

    vertex[8] = vert2.x;
    vertex[9] = vert2.y;
    vertex[10] = vert2.z;
    vertex[11] = norm2.x;
    vertex[12] = norm2.y;
    vertex[13] = norm2.z;
    vertex[14] = coordsTwo.x;
    vertex[15] = coordsTwo.y;

    vertex[16] = vert3.x;
    vertex[17] = vert3.y;
    vertex[18] = vert3.z;
    vertex[19] = norm3.x;
    vertex[20] = norm3.y;
    vertex[21] = norm3.z;
    vertex[22] = coordsThree.x;
    vertex[23] = coordsThree.y;

    vertex[24] = vert4.x;
    vertex[25] = vert4.y;
    vertex[26] = vert4.z;
    vertex[27] = norm4.x;
    vertex[28] = norm4.y;
    vertex[29] = norm4.z;
    vertex[30] = coordsFour.x;
    vertex[31] = coordsFour.y;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    //Initialize Info for OpenGL
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex),
                 &vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),
                          (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),
                          (void *) (3*sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),
                          (void *) (6*sizeof(float)));
}

void SquareTile::draw(const Shader &shader) const {
    useTexture(texture);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SquareTile::setVertexes(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    vert1 = v1;
    vert2 = v2;
    vert3 = v3;
    vert4 = v4;

    updateVertex();
}

glm::vec3 SquareTile::getVert1() const {
    return vert1;
}

glm::vec3 SquareTile::getVert2() const {
    return vert2;
}

glm::vec3 SquareTile::getVert3() const {
    return vert3;
}

glm::vec3 SquareTile::getVert4() const {
    return vert4;
}

void SquareTile::setVert1(const glm::vec3 &v) {
    vert1 = v;
    updateVertex();
}

void SquareTile::setVert2(const glm::vec3 &v) {
    vert2 = v;
    updateVertex();
}

void SquareTile::setVert3(const glm::vec3 &v) {
    vert3 = v;
    updateVertex();
}

void SquareTile::setVert4(const glm::vec3 &v) {
    vert4 = v;
    updateVertex();
}