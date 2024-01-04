//
// Created by Caleb Rutledge on 12/31/23.
//
#pragma once

#include <iostream>
#include "glew.h"
#include "SDL_opengl.h"
#include "Shader.h"
#include "Texture.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Camera.h"
#include "OpenGlWindow.h"


enum class GameState {
    PLAY,
    EXIT
};


class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void stopSystems();
    void gameLoop();
    void processInput();
    void drawGame();
    void setTriangle();
    void drawBuffered();

    SDL_Window* _window;
    SDL_GLContext _context;

    int _screenWidth;
    int _screenHeight;

    GameState _gameState;
    Shader _shader;
    Texture _texture;
    Camera _camera;

    unsigned int _VAO;
    unsigned int _VBO;
    unsigned int _EBO;

    Uint64 _currentFrame;
    Uint64 _lastFrame;
    float _deltaTime;
    float _elapsedMS;
    Uint16 _frameInt;
};


