//
// Created by Caleb Rutledge on 2/9/24.
//


#include "SceneLoader.h"
#include <fstream>

Model SceneLoader::getModelFromDisk(std::ifstream &stream) {
    Model m;
    cereal::BinaryInputArchive archive(stream);
    archive(m);
    m.loadModel(m.src);
    return m;
}

DirectionLight SceneLoader::getDirectionLightFromDisk(std::ifstream &stream) {
    DirectionLight light;
    cereal::BinaryInputArchive archive(stream);
    archive(light);
    return light;
}

PointLight SceneLoader::getPointLightFromDisk(std::ifstream &stream) {
    PointLight light;
    cereal::BinaryInputArchive archive(stream);
    archive(light);
    return light;
}

Scene SceneLoader::getSceneFromDisk(const std::string &path) {

    Scene s;
    std::ifstream stream;
    stream.open(path, std::ios::binary);

    char type;
    while (stream.get(type)) {
        switch (type) {
            case MODEL_LOAD_CODE:
                s.models.emplace_back(getModelFromDisk(stream));
                break;
            case DIRLIGHT_LOAD_CODE:
                s.dirLight = getDirectionLightFromDisk(stream);
                break;
            case POINTLIGHT_LOAD_CODE:
                s.pointLights.emplace_back(getPointLightFromDisk(stream));
                break;
            default:
                exit(492);
        }
    }

    return s;
}
