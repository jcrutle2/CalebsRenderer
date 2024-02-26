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
#include "../Entities/Player.h"


enum class GameState {
    PLAY,
    EXIT
};

enum KeysPressed {
    KEY_PRESSED_W,
    KEY_PRESSED_A,
    KEY_PRESSED_S,
    KEY_PRESSED_D,
    KEY_PRESSED_SPACE,
    KEY_PRESSED_ESC
};


class Game
{
public:
    Game();
    Game(const std::string &scenePath);
    ~Game();

    void run();

private:
    void processInput();
    void processInputUnpaused(SDL_Event * e);
    void processInputPaused(SDL_Event * e);

    bool keysPressed[sizeof(enum KeysPressed)];

    Renderer _renderer;
    Camera _camera;
    Scene _scene;

    GameState _gameState;
};


