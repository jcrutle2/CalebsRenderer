//
// Created by Caleb Rutledge on 2/21/24.
//

#ifndef CALEBSRENDERER_HITBOX_H
#define CALEBSRENDERER_HITBOX_H

#include "glm.hpp"
#include "cereal/access.hpp"

class Hitbox {
public:
    Hitbox();
    void setVerts(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4, const glm::vec3 &v5, const glm::vec3 &v6, const glm::vec3 &v7);

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive &ar);
    glm::vec3 verts[8];
};


#endif //CALEBSRENDERER_HITBOX_H
