//
// Created by Caleb Rutledge on 1/4/24.
//

#ifndef OPENGL_TESTS_OPENGLWINDOW_H
#define OPENGL_TESTS_OPENGLWINDOW_H

#include "SDL.h"
#include "glew.h"
#include "Shader.h"
#include "Model.h"
#include <iostream>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Light.h"
#include "Camera.h"

class OpenGLWindow {
    public:
        OpenGLWindow();
        OpenGLWindow(int screenWidth, int screenHeight);
        ~OpenGLWindow();
        void initSystems();
        void stopSystems();
        void update();
        void setTriangle();
        void drawBuffered();
        void toggleRenderMode();

        float getElapsedMS();

        Camera camera;

private:
        void logFrames();
        SDL_Window* _window;
        SDL_GLContext _context;

        Shader _shader;
        Texture _texture;
        std::vector<Model> _models;

        std::vector<DirectionLight> _dirLights;
        std::vector<PointLight> _pointLights;

        unsigned int _VAO;
        unsigned int _VBO;
        unsigned int _EBO;

        int _screenWidth;
        int _screenHeight;

        Uint64 _renderMode;

        Uint64 _currentFrame;
        Uint64 _lastFrame;
        float _deltaTime;
        float _elapsedMS;
        Uint16 _frameInt;
};


#endif //OPENGL_TESTS_OPENGLWINDOW_H
