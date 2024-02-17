//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Tile.h"

Tile::Tile(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4) {
    vert1 = v1;
    vert2 = v2;
    vert3 = v3;
    vert4 = v4;

    updateVertex();
    setup();
    newTexture(texture, "Assets/Textures/error.png", "png");
}

void Tile::updateVertex() {
    vertex[0] = vert1.x;
    vertex[1] = vert1.y;
    vertex[2] = vert1.z;
    vertex[3] = 1.0f;
    vertex[4] = 1.0f;

    vertex[5] = vert2.x;
    vertex[6] = vert2.y;
    vertex[7] = vert2.z;
    vertex[8] = 0.0f;
    vertex[9] = 1.0f;

    vertex[10] = vert3.x;
    vertex[11] = vert3.y;
    vertex[12] = vert3.z;
    vertex[13] = 0.0f;
    vertex[14] = 0.0f;

    vertex[15] = vert4.x;
    vertex[16] = vert4.y;
    vertex[17] = vert4.z;
    vertex[18] = 1.0f;
    vertex[19] = 0.0f;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
                          (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float),
                          (void *) (3*sizeof(float)));
}

void Tile::draw(const Shader &shader) const {
    glm::mat4 model(1.0f);
    shader.setModel(model);

    useTexture(texture);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}