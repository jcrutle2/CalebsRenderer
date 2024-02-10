//
// Created by Caleb Rutledge on 2/9/24.
//

#include "SceneLoader.h"
#include <fstream>

void SceneLoader::storeModelInfo(const Model &m , std::ofstream &stream) {
    auto info = getModelInfo(m);
    stream.put(MODEL_LOAD_CODE);
    cereal::BinaryOutputArchive archive(stream);
    archive(info);
}

void SceneLoader::storePointLight(const PointLight &p, std::ofstream &stream) {
    stream.put(POINTLIGHT_LOAD_CODE);
    cereal::BinaryOutputArchive archive(stream);
    archive(p);
}

void SceneLoader::storeDirectionLight(const DirectionLight &d, std::ofstream &stream) {
    stream.put(DIRLIGHT_LOAD_CODE);
    cereal::BinaryOutputArchive archive(stream);
    archive(d);
}

void SceneLoader::storeScene(const Scene &s, const std::string &path) {
    std::ofstream stream;
    stream.open(path, std::ios::binary);
    for (const Model &m : s.models) {
        storeModelInfo(m, stream);
    }
    storeDirectionLight(s.dirLight, stream);
    for (const PointLight &p : s.pointLights) {
        storePointLight(p, stream);
    }
}