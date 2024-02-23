//
// Created by Caleb Rutledge on 2/22/24.
//

#include "Physics.h"

#define COLLISION_DETECTOR_AXIS_CHECK(axis) {                                               \
float p0 = glm::dot(v0, axis);                                                              \
float p1 = glm::dot(v1, axis);                                                              \
float p2 = glm::dot(v2, axis);                                                              \
float r = e.getHitboxExtents().x * abs(glm::dot(u0, axis)) +                                \
          e.getHitboxExtents().y * abs(glm::dot(u1, axis)) +                                \
          e.getHitboxExtents().z * abs(glm::dot(u2, axis));                                 \
if (std::max(-std::max(p0, std::max(p1, p2)), std::min(p0, std::min(p1, p2))) > r) {        \
    return false;                                                                           \
}                                                                                           \
}                                                                                           \

bool Physics::collision(Triangle &t, Entity &e) {
    // get triangle vertices to center
    glm::vec3 v0 = t.v0 - e.getPosition();
    glm::vec3 v1 = t.v1 - e.getPosition();
    glm::vec3 v2 = t.v2 - e.getPosition();

    // vectors of triangle sides
    glm::vec3 f0 = v1 - v0; // B - A
    glm::vec3 f1 = v2 - v1; // C - B
    glm::vec3 f2 = v0 - v2; // A - C

    // 3 AABB normals
    glm::vec3 u0 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 u1 = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 u2 = glm::vec3(0.0f, 0.0f, 1.0f);

    // 9 Axis Normals
    glm::vec3 axis_u0_f0 = glm::cross(u0, f0);
    glm::vec3 axis_u0_f1 = glm::cross(u0, f1);
    glm::vec3 axis_u0_f2 = glm::cross(u0, f2);
    glm::vec3 axis_u1_f0 = glm::cross(u1, f0);
    glm::vec3 axis_u1_f1 = glm::cross(u1, f1);
    glm::vec3 axis_u1_f2 = glm::cross(u1, f2);
    glm::vec3 axis_u2_f0 = glm::cross(u2, f0);
    glm::vec3 axis_u2_f1 = glm::cross(u2, f1);
    glm::vec3 axis_u2_f2 = glm::cross(u2, f2);

    // 1 triangle normal
    glm::vec3 triangleNormal = glm::cross(f0, f1);

    // Test axises
    COLLISION_DETECTOR_AXIS_CHECK(u0);
    COLLISION_DETECTOR_AXIS_CHECK(u1);
    COLLISION_DETECTOR_AXIS_CHECK(u2);

    COLLISION_DETECTOR_AXIS_CHECK(axis_u0_f0);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u0_f1);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u0_f2);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u1_f0);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u1_f1);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u1_f2);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u2_f0);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u2_f1);
    COLLISION_DETECTOR_AXIS_CHECK(axis_u2_f2);

    COLLISION_DETECTOR_AXIS_CHECK(triangleNormal);

    return true;
}

void Physics::detectCollision(Scene &s) {
    s.player.onGround = false;
    for (auto &b : s.boxes) {
        for (int i = 0; i < (2 * b.getTileList().size()); i++) {
            auto tri = b.getTriangle(i);
            if (b.getActive(i / 2)) {
                if (collision(tri, s.player)) {
                    // std::cout << "COLLISION DETECTED" << std::endl;
                    glm::vec3 nHat = glm::normalize(glm::cross(tri.v0 - tri.v1, tri.v1 - tri.v2));
                    float dot = glm::dot(s.player.getVelocity(), nHat);
                    glm::vec3 proj = nHat * dot;
                    if (dot < 0) {
                        s.player.velocity -= proj;
                    }
                    if (nHat.y >= abs(nHat.x) && nHat.y >= abs(nHat.z)) {
                        s.player.onGround = true;
                    }
                }
            }
        }
    }
}