//
// Created by Caleb Rutledge on 1/3/24.
//

#include "Headers/Camera.h"
#include <iostream>

Camera::Camera() {
    _view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
    _zoom = 45.0f;

    _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    _pitch = 0.0f;
    _yaw = -90.0f;
    _sensitivity = 0.1f;
    _zoomSensitivity = 1.0f;
}

Camera::Camera(glm::vec3 camP, glm::vec3 camF, glm::vec3 camU) {
    _view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);

    _cameraPos = camP;
    _cameraFront = camF;
    _cameraUp = camU;
    _pitch = 0.0f;
    _yaw = -90.0f;
    _sensitivity = 0.1f;
    _zoomSensitivity = 1.0f;
}

Camera::~Camera() = default;

void Camera::moveForward(const float speed) {
    _cameraPos += speed * _cameraFront;
}

void Camera::moveBackward(const float speed) {
    _cameraPos -= speed * _cameraFront;
}

void Camera::moveRight(const float speed) {
    _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) *
                  speed;
}

void Camera::moveLeft(const float speed) {
    _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) *
                  speed;
}

void Camera::moveUp(const float speed) {
    _cameraPos += speed * _cameraUp;
}

void Camera::moveDown(const float speed) {
    _cameraPos -= speed * _cameraUp;
}

void Camera::updateDirection(int32_t xMovement, int32_t yMovement) {
    _yaw += xMovement * _sensitivity;
    _pitch -= yMovement * _sensitivity;

    // ensure camera doesn't flip over vertical axis
    if(_pitch > 89.0f)
        _pitch = 89.0f;
    if(_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    direction.y = sin(glm::radians(_pitch));
    direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(direction);
}

void Camera::updateZoom(int32_t zoom) {
    _zoom -= zoom * _zoomSensitivity;

    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > 45.0f)
        _zoom = 45.0f;
}

void Camera::updateView() {
    _view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

glm::mat4 Camera::getView() {
    updateView();
    return _view;
}

glm::mat4 Camera::getPerspective() {
    return glm::perspective(glm::radians(_zoom), 800.0f / 600.0f, 0.1f,
                            100.0f);
}