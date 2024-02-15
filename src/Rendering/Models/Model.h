//
// Created by Caleb Rutledge on 1/9/24.
//

#ifndef OPENGL_TESTS_MODEL_H
#define OPENGL_TESTS_MODEL_H

#include "Mesh.h"
#include "Importer.hpp"
#include "postprocess.h"
#include <map>
#include "../Scene/ModelInfo.h"

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;
    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;
};

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);

class Model {
public:
    Model(std::string n, std::string path, glm::vec3 pos= glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scl = glm::vec3(1.0f, 1.0f, 1.0f));
    Model(const ModelInfo &m);
    Model();

    std::string name;

    void Draw(Shader shader);

    // model location
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotation;
    glm::vec3 scale;

    std::string src;

    template<class Archive>
    void serialize(Archive &ar);
    void loadModel(std::string path);

private:
    // Serialization

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
