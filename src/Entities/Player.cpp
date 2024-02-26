//
// Created by Caleb Rutledge on 2/22/24.
//

#include "Player.h"

Player::Player() : Entity() {
    position = PLAYER_POSITION_DEFAULT;
    camera = Camera();
    cameraOffset = glm::vec3(0.0,1.0,0.0f);
    camera.cameraPos = position + cameraOffset;
    direction = glm::vec3(0.0,0.0,-1.0);
    relativeSpeed = glm::vec3(0.0,0.0,0.0);
}

Player::Player(Player &p) : Entity(p) {
    relativeSpeed = p.relativeSpeed;
    cameraOffset = p.cameraOffset;
    camera = p.camera;
}

Player& Player::operator=(const Player &p) {
    src = p.src;
    loadModel(src);
    name = p.name;
    position = p.position;
    rotationAxis = p.rotationAxis;
    rotation = p.rotation;
    scale = p.scale;
    onGround = p.onGround;
    hitbox = p.hitbox;
    velocity = p.velocity;
    direction = p.direction;
    relativeSpeed = p.relativeSpeed;
    cameraOffset = p.cameraOffset;
    camera = p.camera;
    return *this;
}

void Player::updatePosition() {
    /*
    if (position.y < 0) {
        position.y = 0;
        velocity.y = 0;
    }
    else if (position.y > 0) {
        velocity.y -= 0.01f;
    }*/

    position += velocity;
    camera.cameraPos = position + cameraOffset;
}

Camera& Player::getCamera() {
    return camera;
}

void Player::updateDirection(int32_t xMovement, int32_t yMovement) {
    direction = camera.updateDirection(xMovement, yMovement);
}

void Player::updateVelocity() {
    velocity = glm::vec3(0.0f, relativeSpeed.y, 0.0f);
    velocity -= relativeSpeed.x * glm::cross(glm::vec3(0,1,0), glm::normalize(direction));
    velocity -= relativeSpeed.z * glm::normalize(glm::vec3(direction.x, 0, direction.z));
}

void Player::setXSpeed(const float &f) {
    relativeSpeed.x = f;
}

void Player::setYSpeed(const float &f) {
    relativeSpeed.y = f;
}

void Player::setZSpeed(const float &f) {
    relativeSpeed.z = f;
}