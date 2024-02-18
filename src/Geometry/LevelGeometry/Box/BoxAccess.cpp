//
// Created by Caleb Rutledge on 2/17/24.
//

#include "Box.h"

glm::vec3 Box::getPosition() const {
    return position;
}

glm::vec3 Box::getRotationAxis() const {
    return rotationAxis;
}

float Box::getRotation() const {
    return rotation;
}

glm::vec3 Box::getScale() const {
    return scale;
}

glm::vec3 Box::getV0() const {
    return boxVertices[0];
}
glm::vec3 Box::getV1() const {
    return boxVertices[1];
}
glm::vec3 Box::getV2() const {
    return boxVertices[2];
}
glm::vec3 Box::getV3() const {
    return boxVertices[3];
}
glm::vec3 Box::getV4() const {
    return boxVertices[4];
}
glm::vec3 Box::getV5() const {
    return boxVertices[5];
}
glm::vec3 Box::getV6() const {
    return boxVertices[6];
}
glm::vec3 Box::getV7() const {
    return boxVertices[7];
}

void Box::setPosition(glm::vec3 pos) {
    position = pos;
}

void Box::setRotationAxis(glm::vec3 rot) {
    rotationAxis = rot;
}

void Box::setRotation(float r) {
    rotation = r;
}

void Box::setScale(glm::vec3 s) {
    scale = s;
}

void Box::setV0(const glm::vec3 &v) {
    boxVertices[0] = v;
    setupCube();
}
void Box::setV1(const glm::vec3 &v) {
    boxVertices[1] = v;
    setupCube();
}
void Box::setV2(const glm::vec3 &v) {
    boxVertices[2] = v;
    setupCube();
}
void Box::setV3(const glm::vec3 &v) {
    boxVertices[3] = v;
    setupCube();
}
void Box::setV4(const glm::vec3 &v) {
    boxVertices[4] = v;
    setupCube();
}
void Box::setV5(const glm::vec3 &v) {
    boxVertices[5] = v;
    setupCube();
}
void Box::setV6(const glm::vec3 &v) {
    boxVertices[6] = v;
    setupCube();
}
void Box::setV7(const glm::vec3 &v) {
    boxVertices[7] = v;
    setupCube();
}