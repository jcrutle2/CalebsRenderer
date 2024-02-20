//
// Created by Caleb Rutledge on 2/9/24.
//

#include "Scene.h"
#include <fstream>

void SceneLoader::storeScene(const Scene &s, const std::string &path) {
    std::ofstream stream;
    stream.open(path, std::ios::binary);
    cereal::BinaryOutputArchive archive(stream);
    archive(s);
}