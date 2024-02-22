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
#include "../Rendering/Camera.h"
#include "../Rendering/Renderer.h"


enum class GameState {
    PLAY,
    EXIT
};


class Editor
{
public:
    Editor();
    ~Editor();

    void run();

private:
    void processInput();
    void processInputUnpaused(SDL_Event * e);
    void processInputPaused(SDL_Event * e);

    Renderer _renderer;
    Camera _camera;
    Scene _scene;

    GameState _gameState;
};


