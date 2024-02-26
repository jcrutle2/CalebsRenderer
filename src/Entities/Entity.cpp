//
// Created by Caleb Rutledge on 2/21/24.
//

#include "Entity.h"

Entity::Entity() : Model() {
    velocity = glm::vec3(0.0f);
}

Entity::Entity(std::string n, std::string path, glm::vec3 pos, glm::vec3 scl) : Model(n, path, pos, scl){
    velocity = glm::vec3(0.0f);
}

Entity::Entity(const Entity &e) : Model(e) {
    velocity = e.velocity;
}

Entity& Entity::operator=(const Entity &e) {
    src = e.src;
    loadModel(src);
    name = e.name;
    position = e.position;
    rotationAxis = e.rotationAxis;
    rotation = e.rotation;
    scale = e.scale;
    onGround = e.onGround;
    hitbox = e.hitbox;
    velocity = e.velocity;
    direction = e.direction;

    return *this;
}

glm::vec3 Entity::getVelocity() const {
    return velocity;
}
glm::vec3 Entity::getPosition() const {
    return position;
}
glm::vec3 Entity::getDirection() const {
    return direction;
}

void Entity::setXVelocity(const float &f) {
    velocity.x = f;
}

void Entity::setYVelocity(const float &f) {
    velocity.y = f;
}

void Entity::setZVelocity(const float &f) {
    velocity.z = f;
}

void Entity::updatePosition() {
    position += velocity;
}

glm::vec3 Entity::getHitboxExtents() const {
    return hitbox.getExtents();
}

bool Entity::isOnGround() const {
    return onGround;
}
