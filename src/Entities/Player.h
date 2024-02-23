//
// Created by Caleb Rutledge on 2/22/24.
//

#ifndef CALEBSRENDERER_PLAYER_H
#define CALEBSRENDERER_PLAYER_H

#include "Entity.h"
#include "../Rendering/Camera.h"

#define PLAYER_POSITION_DEFAULT (glm::vec3(0.0f, 1.0f, 0.0f))

class Player : public Entity {
    friend class Physics;
public:
    Player();
    ~Player() = default;

    void updatePosition() override;
    Camera& getCamera();
    void updateDirection(int32_t xMovement, int32_t yMovement);
    void updateVelocity();

    void setXSpeed(const float &f);
    void setYSpeed(const float &f);
    void setZSpeed(const float &f);

private:
    glm::vec3 relativeSpeed;
    glm::vec3 cameraOffset;
    Camera camera;
};


#endif //CALEBSRENDERER_PLAYER_H
