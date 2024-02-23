//
// Created by Caleb Rutledge on 2/23/24.
//

#include "Physics.h"

void Physics::calculatePhysics(Scene &s) {
    s.player.updateVelocity();
    calculateGravity(s.player);
    detectCollision(s);
}

void Physics::calculateGravity(Player &p) {
    p.velocity -= PHYSICS_GRAVITY_CONSTANT;
    p.relativeSpeed -= PHYSICS_GRAVITY_CONSTANT;
}
