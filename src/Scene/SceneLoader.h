//
// Created by Caleb Rutledge on 2/9/24.
//
#pragma once

#ifndef CALEBSRENDERER_SCENELOADER_H
#define CALEBSRENDERER_SCENELOADER_H

#include <vector>
#include "../Geometry/Models/Model.h"
#include "../Environment/Light/Light.h"
#include "glm.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/access.hpp"
#include "ModelInfo.h"
#include "Scene.h"
#include "../Environment/Skybox/Skybox.h"

namespace SceneLoader {

    // Stores Model on the Disk
    void storeModel(const Model &m, std::ofstream &stream);
    // Stores PointLight on Disk
    void storePointLight(const PointLight &p, std::ofstream &stream);
    // Stores DirectionLight on Disk
    void storeDirectionLight(const DirectionLight &d, std::ofstream &stream);
    // Stores Skybox on Disk
    void storeSkybox(const Skybox &s, std::ofstream &stream);
    // Stores Scene to Disk
    void storeScene(const Scene &s, const std::string &path);
    // Gets Model from Disk
    Model getModelFromDisk(std::ifstream &stream);
    // Load Direction Light from disk
    DirectionLight getDirectionLightFromDisk(std::ifstream &stream);
    // Load PointLight from Disk
    PointLight getPointLightFromDisk(std::ifstream &stream);
    // Load Skybox from Disk
    Skybox getSkyboxFromDisk(std::ifstream &stream);
    // Load Scene from Disk
    Scene getSceneFromDisk(const std::string &path);
}

#endif //CALEBSRENDERER_SCENELOADER_H
