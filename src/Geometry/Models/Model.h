//
// Created by Caleb Rutledge on 1/9/24.
//

#ifndef OPENGL_TESTS_MODEL_H
#define OPENGL_TESTS_MODEL_H

#pragma once

#include "Mesh.h"
#include "postprocess.h"
#include <map>
#include "../../Environment/Light/Light.h"

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;
    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;
};

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    Model(std::string n, std::string path, glm::vec3 pos= glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scl = glm::vec3(1.0f, 1.0f, 1.0f));
    Model();
    Model(const Model &m);
    Model& operator= (const Model &m);

    // Getters
    std::string getName() const;
    glm::vec3 getPosition() const;
    glm::vec3 getRotationAxis() const;
    float getRotation() const;
    glm::vec3 getScale() const;
    std::string getSrc() const;
    std::vector<PointLight>& getLightsList();
    std::vector<PointLight> getLightsListConst() const;

    // Setters
    void setName(const std::string &n);
    void setPosition(const glm::vec3 &v);
    void setRotationAxis(const glm::vec3 &v);
    void setRotation(const float &v);
    void setScale(const glm::vec3 &v);
    void pushBackLight(std::string name);


    template<class S>
    void Draw(S shader);

    void loadModel(std::string path);

protected:
    std::string name;
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotation;
    glm::vec3 scale;
    std::string src;
    std::vector<PointLight> lights;

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void save(Archive &ar) const;
    template<class Archive>
    void load(Archive &ar);

    // mesh info
    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;

    // private loading functions
    void processNode(aiNode *const node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // Texture Info
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};




#endif //OPENGL_TESTS_MODEL_H
