//
// Created by Caleb Rutledge on 1/4/24.
//

#ifndef OPENGL_TESTS_OPENGLWINDOW_H
#define OPENGL_TESTS_OPENGLWINDOW_H

#include "SDL.h"
#include "glew.h"
#include <iostream>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "../Rendering/Camera.h"
#include "../Rendering/Scene/Scene.h"
#include "../UI/UI.h"
#include "../Rendering/Skybox/Skybox.h"
#include "../Rendering/Models/Shader.h"


class OpenGLWindow {
    public:
        explicit OpenGLWindow(int screenWidth = 1024, int screenHeight = 768);
        ~OpenGLWindow();
        void initSystems();
        void stopSystems();
        void update();
        void drawBuffered();
        void toggleRenderMode();

        [[nodiscard]] float getElapsedMS() const;

        Camera camera;
        Shader shader;

        Scene scene;

private:
        void logFrames();
        SDL_Window* _window;
        SDL_GLContext _context;

        Texture _texture;

        unsigned int VAO{};
        unsigned int VBO{};
        unsigned int EBO{};

        int _screenWidth;
        int _screenHeight;

        Uint64 _renderMode{};

        Uint64 _currentFrame{};
        Uint64 _lastFrame{};
        float _deltaTime{};
        float _elapsedMS{};
        Uint16 _frameInt{};
        std::string _frameRate;
};


#endif //OPENGL_TESTS_OPENGLWINDOW_H
