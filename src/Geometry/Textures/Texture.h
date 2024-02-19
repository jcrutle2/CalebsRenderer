//
// Created by Caleb Rutledge on 2/18/24.
//

#ifndef CALEBSRENDERER_TEXTURE_H
#define CALEBSRENDERER_TEXTURE_H

#endif //CALEBSRENDERER_TEXTURE_H
#include <string>
#include <assimp/Importer.hpp>
#include <filesystem>

struct Texture {
public:
    unsigned int id;
    std::string type;
    aiString path;
};

namespace TextureGlobals {
    extern std::vector<Texture> loaded;
    std::string shorten(const std::string &s);
    void loadAllTextures();
    std::string fileExtension(const std::string &file);
}

void newTexture(Texture &t, const char* path, const char* type);

void useTexture(const Texture &t);