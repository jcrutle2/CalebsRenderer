//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Tile.h"

Tile::Tile(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    vert1 = v1;
    vert2 = v2;
    vert3 = v3;
    vert4 = v4;

    textureScale = TEXTURE_SCALE_DEFAULT;

    updateVertex();
    setup();
    newTexture(texture, "Assets/Textures/error.png", "png");
}

void Tile::updateVertex() {
    glm::vec3 norm1 = glm::normalize(glm::cross(vert2 - vert1, vert4 - vert1));
    glm::vec3 norm2 = glm::normalize(glm::cross(vert3 - vert2, vert1 - vert2));
    glm::vec3 norm3 = glm::normalize(glm::cross(vert4 - vert3, vert2 - vert3));
    glm::vec3 norm4 = glm::normalize(glm::cross(vert1 - vert4, vert3 - vert4));

    glm::vec3 rHat = glm::normalize(vert4 - vert3);
    float rMag = glm::length(vert4 - vert3);

    glm::vec3 vecTwoThree = vert2 - vert3;
    glm::vec3 vecOneThree = vert1 - vert3;

    float xOne = glm::length(rHat * glm::dot(rHat, vecOneThree));
    float yOne = glm::length(glm::vec3((vecOneThree) - (rHat * glm::dot(rHat, vecOneThree))));
    float xTwo = glm::length(rHat * glm::dot(rHat, vecTwoThree));
    float yTwo = glm::length((vecTwoThree) - (rHat * glm::dot(rHat, vecTwoThree)));

    vertex[0] = vert1.x;
    vertex[1] = vert1.y;
    vertex[2] = vert1.z;
    vertex[3] = norm1.x;
    vertex[4] = norm1.y;
    vertex[5] = norm1.z;
    vertex[6] = xOne * textureScale;
    vertex[7] = yOne * textureScale;

    vertex[8] = vert2.x;
    vertex[9] = vert2.y;
    vertex[10] = vert2.z;
    vertex[11] = norm2.x;
    vertex[12] = norm2.y;
    vertex[13] = norm2.z;
    vertex[14] = xTwo * textureScale;
    vertex[15] = yTwo * textureScale;

    vertex[16] = vert3.x;
    vertex[17] = vert3.y;
    vertex[18] = vert3.z;
    vertex[19] = norm3.x;
    vertex[20] = norm3.y;
    vertex[21] = norm3.z;
    vertex[22] = 0.0f;
    vertex[23] = 0.0f;

    vertex[24] = vert4.x;
    vertex[25] = vert4.y;
    vertex[26] = vert4.z;
    vertex[27] = norm4.x;
    vertex[28] = norm4.y;
    vertex[29] = norm4.z;
    vertex[30] = rMag * textureScale;
    vertex[31] = 0.0f;
}

void Tile::setup() {
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

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

void Tile::draw(const Shader &shader) const {
    glm::mat4 model(1.0f);
    shader.setModel(model);

    useTexture(texture);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}