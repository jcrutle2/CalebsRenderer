//
// Created by Caleb Rutledge on 2/21/24.
//

#include "Entity.h"

Entity::Entity() : Model() {

}

Entity::Entity(std::string n, std::string path, glm::vec3 pos, glm::vec3 scl) : Model(n, path, pos, scl){

}

Entity::Entity(const Entity &e) : Model(e) {

}

Entity &Entity::operator=(const Entity &e) {
    return *this;
}

