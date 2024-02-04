//
// Created by Caleb Rutledge on 12/31/23.
//
#pragma once

#include <iostream>
#include "glew.h"
#include "SDL_opengl.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Camera.h"
#include "OpenGLWindow.h"


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
    void gameLoop();
    void processInput();
    void processInputUnpaused(SDL_Event * e);
    void processInputPaused(SDL_Event * e);

    OpenGLWindow _window;

    GameState _gameState;
};


