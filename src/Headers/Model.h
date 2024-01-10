//
// Created by Caleb Rutledge on 1/9/24.
//

#ifndef OPENGL_TESTS_MODEL_H
#define OPENGL_TESTS_MODEL_H

#include "Mesh.h"
#include "Importer.hpp"
#include "postprocess.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);

class Model {
public:
    Model(std::string path);

    Model();

    void Draw(Shader shader);

private:
    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);

    void processNode(aiNode *const node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};




#endif //OPENGL_TESTS_MODEL_H
