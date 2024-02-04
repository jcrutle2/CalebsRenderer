//
// Created by Caleb Rutledge on 1/3/24.
//

#ifndef OPENGL_TESTS_CAMERA_H
#define OPENGL_TESTS_CAMERA_H
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <SDL.h>

typedef enum CameraState {
    CAMERA_STATE_PAUSED,
    CAMERA_STATE_UNPAUSED,
} CameraState;

class Camera {
    public:
    explicit Camera(glm::vec3 camP = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 camF = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 camU = glm::vec3(0.0f, 1.0f, 0.0f));
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

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    CameraState state;
    void toggleCameraState();

private:
    glm::mat4 _view;
    float _zoom;
    float _yaw;
    float _pitch;
    float _sensitivity;
    float _zoomSensitivity;
};


#endif //OPENGL_TESTS_CAMERA_H
