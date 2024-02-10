//
// Created by Caleb Rutledge on 2/9/24.
//

#include "Scene.h"
#include "ModelInfo.h"
#include "SceneLoader.h"
#include <fstream>

ModelInfo SceneLoader::getModelInfo(const Model &m) {
    ModelInfo info;

    std::strcpy(info.name, m.name);
    std::strcpy(info.path, m.src.c_str());
    info.position[0] = m.position.x;
    info.position[1] = m.position.y;
    info.position[2] = m.position.z;
    info.rotation = m.rotation;
    info.rotationAxis[0] = m.rotationAxis.x;
    info.rotationAxis[1] = m.rotationAxis.y;
    info.rotationAxis[2] = m.rotationAxis.z;
    info.scale[0] = m.scale.x;
    info.scale[1] = m.scale.y;
    info.scale[2] = m.scale.x;

    return info;
}

template<class Archive>
void ModelInfo::serialize(Archive &ar) {
    ar (name);
    ar (path);
    ar (position);
    ar (rotation);
    ar (rotationAxis);
    ar (scale);
}

template<class Archive>
void PointLight::serialize(Archive &ar) {
    ar(position.x);
    ar(position.y);
    ar(position.z);
    ar(ambient.r);
    ar(ambient.g);
    ar(ambient.b);
    ar(specular.r);
    ar(specular.g);
    ar(specular.b);
    ar(diffuse.r);
    ar(diffuse.g);
    ar(diffuse.b);
    ar(constant);
    ar(linear);
    ar(quadratic);
}


template<class Archive>
void DirectionLight::serialize(Archive &ar) {
    ar(direction.x);
    ar(direction.y);
    ar(direction.z);
    ar(ambient.r);
    ar(ambient.g);
    ar(ambient.b);
    ar(specular.r);
    ar(specular.g);
    ar(specular.b);
    ar(diffuse.r);
    ar(diffuse.g);
    ar(diffuse.b);
}

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

ModelInfo SceneLoader::getModelInfoFromDisk(std::ifstream &stream) {
    ModelInfo info;
    cereal::BinaryInputArchive archive(stream);
    archive(info);
    return info;
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
                s.models.emplace_back(getModelInfoFromDisk(stream));
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