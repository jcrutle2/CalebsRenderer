//
// Created by Caleb Rutledge on 2/9/24.
//

#ifndef CALEBSRENDERER_SCENE_H
#define CALEBSRENDERER_SCENE_H
#pragma once

#include <vector>
#include "../Rendering/Models/Model.h"
#include "../Rendering/Light/Light.h"
#include <glm.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>

// Codes that the machine uses to identify type of data being read from device
#define MODEL_LOAD_CODE '\xff'
#define DIRLIGHT_LOAD_CODE '\xfe'
#define POINTLIGHT_LOAD_CODE '\xfd'

// A Struct Holding All Information in a Scene
struct Scene {
public:
    std::vector<Model> models;
    DirectionLight dirLight;
    std::vector<PointLight> pointLights;

};
#endif //CALEBSRENDERER_SCENE_H
