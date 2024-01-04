//
// Created by Caleb Rutledge on 1/4/24.
//

#ifndef OPENGL_TESTS_OPENGLWINDOW_H
#define OPENGL_TESTS_OPENGLWINDOW_H

#include "SDL.h"
#include "glew.h"
#include "Shader.h"
#include "Texture.h"
#include <iostream>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>

class OpenGLWindow {
    public:
        OpenGLWindow();
        OpenGLWindow(int screenWidth, int screenHeight);
        ~OpenGLWindow();
        void initSystems();
        void stopSystems();
        void update();
        void setTriangle();
        void drawBuffered(glm::mat4 viewMat, glm::mat4 projectionMat);

        float getElapsedMS();

private:
        void logFrames();
        SDL_Window* _window;
        SDL_GLContext _context;

        Shader _shader;
        Texture _texture;


        unsigned int _VAO;
        unsigned int _VBO;
        unsigned int _EBO;

        int _screenWidth;
        int _screenHeight;

        Uint64 _currentFrame;
        Uint64 _lastFrame;
        float _deltaTime;
        float _elapsedMS;
        Uint16 _frameInt;
};


#endif //OPENGL_TESTS_OPENGLWINDOW_H
