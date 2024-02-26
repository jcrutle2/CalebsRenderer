//
// Created by Caleb Rutledge on 2/21/24.
//

#ifndef CALEBSRENDERER_HITBOX_H
#define CALEBSRENDERER_HITBOX_H

#include "glm.hpp"
#include "cereal/access.hpp"

#define HITBOX_VO_DEFAULT = (glm::vec3(0.0f))

class Hitbox {
public:
    Hitbox();
    Hitbox(Hitbox &h);
    Hitbox& operator=(const Hitbox &h);
    void setExtents(const glm::vec3 &v);
    glm::vec3 getExtents() const;

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive &ar);
    glm::vec3 extents;
};


#endif //CALEBSRENDERER_HITBOX_H
