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

    // Getters
    glm::vec3 getVelocity() const;
    glm::vec3 getPosition() const;
    glm::vec3 getHitboxExtents() const;
    glm::vec3 getDirection() const;
    bool isOnGround() const;

    // Setters
    void setXVelocity(const float &f);
    void setYVelocity(const float &f);
    void setZVelocity(const float &f);


    // Update Position
    virtual void updatePosition();

protected:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void save(Archive &ar) const;
    template<class Archive>
    void load(Archive &ar);

    bool onGround;

    // Hitbox
    Hitbox hitbox;

    // Velocity
    glm::vec3 velocity;
    glm::vec3 direction;
};


#endif //CALEBSRENDERER_ENTITY_H
