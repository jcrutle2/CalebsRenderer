//
// Created by Caleb Rutledge on 2/21/24.
//

#ifndef CALEBSRENDERER_ENTITY_H
#define CALEBSRENDERER_ENTITY_H

#include <string>
#include "../Geometry/Models/Model.h"
#include "Hitbox.h"

class Entity : public Model {
public:
    Entity(std::string n, std::string path, glm::vec3 pos= glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scl = glm::vec3(1.0f, 1.0f, 1.0f));
    Entity();
    Entity(const Entity &e);
    Entity& operator= (const Entity &e);

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void save(Archive &ar) const;
    template<class Archive>
    void load(Archive &ar);
    Hitbox hitbox;
};


#endif //CALEBSRENDERER_ENTITY_H
