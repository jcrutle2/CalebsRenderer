//
// Created by Caleb Rutledge on 2/9/24.
//

#ifndef CALEBSRENDERER_SCENE_H
#define CALEBSRENDERER_SCENE_H
#pragma once

#include <vector>
#include "../Geometry/Models/Model.h"
#include "../Environment/Light/Light.h"
#include "glm.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/access.hpp"
#include "../Environment/Skybox/Skybox.h"
#include "../Geometry/LevelGeometry/Box/Box.h"
#include "../Entities/Entity.h"

// A Struct Holding All Information in a Scene
struct Scene {
public:
    std::vector<Entity> entities;
    DirectionLight dirLight;
    std::vector<PointLight> pointLights;
    Skybox skybox;
    std::vector<Box> boxes;

    template<class Archive>
    void serialize(Archive &ar);
};

namespace SceneLoader {
    // Stores Scene to Disk
    void storeScene(const Scene &s, const std::string &path);
    // Load Scene from Disk
    Scene getSceneFromDisk(const std::string &path);
}
#endif //CALEBSRENDERER_SCENE_H
