//
// Created by Caleb Rutledge on 2/9/24.
//
#pragma once

#ifndef CALEBSRENDERER_SCENELOADER_H
#define CALEBSRENDERER_SCENELOADER_H

#include <vector>
#include "../Headers/Model.h"
#include "../Headers/Light.h"
#include <glm.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>
#include "ModelInfo.h"
#include "Scene.h"

namespace SceneLoader {
    // Holds Model Information In A Way That Can Be Read By The Disk

    // Converts a Model into the Disk Storage Format
    ModelInfo getModelInfo(const Model &m);
    // Stores Model on the Disk
    void storeModelInfo(const Model &m, std::ofstream &stream);
    // Stores PointLight on Disk
    void storePointLight(const PointLight &p, std::ofstream &stream);
    // Stores DirectionLight on Disk
    void storeDirectionLight(const DirectionLight &d, std::ofstream &stream);
    // Stores Scene to Disk
    void storeScene(const Scene &s, const std::string &path);
    // Gets ModelInfo from disk
    ModelInfo getModelInfoFromDisk(std::ifstream &stream);
    // Load Direction Light from disk
    DirectionLight getDirectionLightFromDisk(std::ifstream &stream);
    // Load PointLight from Disk
    PointLight getPointLightFromDisk(std::ifstream &stream);
    // Load Scene from Disk
    Scene getSceneFromDisk(const std::string &path);
}

#endif //CALEBSRENDERER_SCENELOADER_H
