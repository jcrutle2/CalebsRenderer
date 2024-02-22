//
// Created by Caleb Rutledge on 1/4/24.
//

#ifndef OPENGL_TESTS_OPENGLWINDOW_H
#define OPENGL_TESTS_OPENGLWINDOW_H

#include "SDL.h"
#include "glew.h"
#include <iostream>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"
#include "../Scene/Scene.h"
#include "../UI/UI.h"
#include "../Environment/Skybox/Skybox.h"
#include "../Geometry/Models/Shader.h"


class Renderer {
    public:
        explicit Renderer(int screenWidth = 1024, int screenHeight = 768);
        ~Renderer();
        void initSystems();
        void stopSystems();
        void update();
        void draw(Scene &scene, Camera &camera);
        void toggleRenderMode();
        std::string getFrameRate() { return _frameRate; };


        [[nodiscard]] float getElapsedMS() const;

        Shader shader;
        Shader tileShader;

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
