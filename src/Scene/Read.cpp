//
// Created by Caleb Rutledge on 2/9/24.
//


#include "Scene.h"
#include <fstream>

Scene SceneLoader::getSceneFromDisk(const std::string &path) {
    Scene s;
    std::ifstream stream;
    stream.open(path, std::ios::binary);

    cereal::BinaryInputArchive archive(stream);
    archive(s);

    return s;
}
