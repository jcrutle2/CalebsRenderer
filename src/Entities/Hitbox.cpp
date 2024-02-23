//
// Created by Caleb Rutledge on 2/21/24.
//

#include "Hitbox.h"

Hitbox::Hitbox() {
    extents = glm::vec3 (1.5f, 1.5f, 1.5f);
}

void Hitbox::setExtents(const glm::vec3 &v) {
    extents = v;
}

glm::vec3 Hitbox::getExtents() const {
    return extents;
}
