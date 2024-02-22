//
// Created by Caleb Rutledge on 12/31/23.
//

#include "Game.h"
#include "imgui_impl_sdl2.h"
#define SPEED 1.5

Game::Game() {
    _gameState = GameState::PLAY;

    _scene = Scene();
    // load lights
    _scene.dirLight = DirectionLight("Direction Light", glm::vec3(0.2f, -0.2f, -0.1f));
    // Test Tiles
    _scene.boxes.emplace_back("Box1", glm::vec3(0.0f,0.0f,0.0f));
}

Game::~Game() = default;

void Game::run() {
    while (_gameState != GameState::EXIT) {
        processInput();

        // Render Geometry and IMGUI
        _renderer.draw(_scene, _camera);

        // Flush to Screen
        _renderer.update();
    }
    _renderer.stopSystems();
}

void Game::processInput() {
    SDL_Event e;
    const float speed = 0.025f * _renderer.getElapsedMS();
    while (SDL_PollEvent(&e)){
        switch (_camera.state) {
            case CAMERA_STATE_UNPAUSED:
                processInputUnpaused(&e);
                break;

            case CAMERA_STATE_PAUSED:
                processInputPaused(&e);
                break;
        }
    }
}

void Game::processInputUnpaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_KEYDOWN:
            switch( e->key.keysym.sym ) {
                case SDLK_w:
                    _camera.moveForward(SPEED);
                    break;
                case SDLK_s:
                    _camera.moveBackward(SPEED);
                    break;
                case SDLK_a:
                    _camera.moveLeft(SPEED);
                    break;
                case SDLK_d:
                    _camera.moveRight(SPEED);
                    break;
                case SDLK_SPACE:
                    _camera.moveUp(SPEED);
                    break;
                case SDLK_LSHIFT:
                    _camera.moveDown(SPEED);
                    break;
                case SDLK_v:
                    _renderer.toggleRenderMode();
                    break;
                case SDLK_ESCAPE:
                    _camera.toggleCameraState();
                    break;
                case SDLK_q:
                    _gameState = GameState::EXIT;
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            _camera.updateDirection(e->motion.xrel, e->motion.yrel);
            break;
        case SDL_MOUSEWHEEL:
            _camera.updateZoom(e->wheel.y);
            break;
        default:
            break;
    }
}

void Game::processInputPaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            _camera.toggleCameraState();
            break;
        case SDL_KEYDOWN:
            switch( e->key.keysym.sym ) {
                case SDLK_ESCAPE:
                    _camera.toggleCameraState();
                    break;

                case SDLK_q:
                    _gameState = GameState::EXIT;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}