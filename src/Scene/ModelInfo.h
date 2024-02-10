//
// Created by Caleb Rutledge on 2/9/24.
//

#ifndef CALEBSRENDERER_MODELINFO_H
#define CALEBSRENDERER_MODELINFO_H
#pragma once


#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>

// Holds Model Information In A Way That Can Be Read By The Disk
struct ModelInfo{
public:
    char name[64];
    char path[256];
    float position[3];
    float rotationAxis[3];
    float rotation;
    float scale[3];

    friend class cereal::access;
    friend class cereal::BinaryInputArchive;
    template<class Archive>
    void serialize(Archive &ar);
};

#endif //CALEBSRENDERER_MODELINFO_H
