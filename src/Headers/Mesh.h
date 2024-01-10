//
// Created by Caleb Rutledge on 1/6/24.
//
#pragma once

#ifndef OPENGL_TESTS_MESH_H
#define OPENGL_TESTS_MESH_H


#include "glew.h"
#include "Shader.h"
#include "glm.hpp"
#include <string>
#include <iostream>
#include "scene.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

void newTexture(Texture &t, const char* path, const char* type);

void useTexture(Texture &t);

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             std::vector<Texture> textures);
        void Draw(Shader &shader);

    private:
        // render data
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};

#endif //OPENGL_TESTS_MESH_H
