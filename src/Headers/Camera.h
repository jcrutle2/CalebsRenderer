//
// Created by Caleb Rutledge on 1/3/24.
//

#ifndef OPENGL_TESTS_CAMERA_H
#define OPENGL_TESTS_CAMERA_H
#include <glm.hpp>
#include <matrix_transform.hpp>


class Camera {
    public:
    Camera();
    Camera(glm::vec3 camP, glm::vec3 camF, glm::vec3 camU);
    ~Camera();

    void moveForward(const float speed);
    void moveBackward(const float speed);
    void moveRight(const float speed);
    void moveLeft(const float speed);
    void moveUp(const float speed);
    void moveDown(const float speed);
    void updateDirection(int32_t xMovement, int32_t yMovement);
    void updateZoom(int32_t zoom);
    void updateView();
    glm::mat4 getView();
    glm::mat4 getPerspective();



private:
    glm::mat4 _view;
    float _zoom;
    glm::vec3 _cameraPos;
    glm::vec3 _cameraFront;
    glm::vec3 _cameraUp;
    float _yaw;
    float _pitch;
    float _sensitivity;
    float _zoomSensitivity;
};


#endif //OPENGL_TESTS_CAMERA_H
