//
// Created by Caleb Rutledge on 1/6/24.
//
#pragma once

#ifndef OPENGL_TESTS_MESH_H
#define OPENGL_TESTS_MESH_H

#define MAX_BONE_INFLUENCE 4
#define MAX_BONE_WEIGHTS 4

#include "glew.h"
#include "glm.hpp"
#include <string>
#include <iostream>
#include "scene.h"
#include "../Textures/Texture.h"

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_WEIGHTS];
};



class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             std::vector<Texture> textures);
        template<class S>
        void Draw(S &shader);

    private:
        // render data
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};

#endif //OPENGL_TESTS_MESH_H
