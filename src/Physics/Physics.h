//
// Created by Caleb Rutledge on 2/22/24.
//

#ifndef CALEBSRENDERER_PHYSICS_H
#define CALEBSRENDERER_PHYSICS_H
#include "../Scene/Scene.h"

#define PHYSICS_GRAVITY_CONSTANT (glm::vec3(0.0f, 0.0015f, 0.0f))


class Physics {
public:
    Physics() = delete;
    static void calculatePhysics(Scene &s);
    static void calculateGravity(Player &p);
    static void detectCollision(Scene &s);

private:
    static bool collision(Triangle &t, Entity &e);
};


#endif //CALEBSRENDERER_PHYSICS_H
