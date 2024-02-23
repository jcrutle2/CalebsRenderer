//
// Created by Caleb Rutledge on 12/31/23.
//

#include "Game.h"
#include "imgui_impl_sdl2.h"
#include "../Physics/Physics.h"
#define PLAYER_SPEED (0.075f)

Game::Game() {
    _gameState = GameState::PLAY;

    _scene = Scene();
    // load lights
    _scene.dirLight = DirectionLight("Direction Light", glm::vec3(0.2f, -0.2f, -0.1f));
    // Test Tiles
    _scene.boxes.emplace_back("Box1", glm::vec3(0.0f,0.0f,0.0f));
}

Game::Game(const std::string &scenePath) {
    _gameState = GameState::PLAY;

    _scene = SceneLoader::getSceneFromDisk(scenePath);

}

Game::~Game() = default;

void Game::run() {
    while (_gameState != GameState::EXIT) {
        for (int i = 0; i < 4; i++) {
            processInput();
            Physics::calculatePhysics(_scene);
            _scene.player.updatePosition();
        }


        // Render Geometry and IMGUI
        _renderer.draw(_scene, _scene.player.getCamera());

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
                    _scene.player.setZSpeed(-PLAYER_SPEED);
                    break;
                case SDLK_s:
                    _scene.player.setZSpeed(PLAYER_SPEED);
                    break;
                case SDLK_a:
                    _scene.player.setXSpeed(-PLAYER_SPEED);
                    break;
                case SDLK_d:
                    _scene.player.setXSpeed(PLAYER_SPEED);
                    break;
                case SDLK_SPACE:
                    if (_scene.player.isOnGround())
                        _scene.player.setYSpeed(1.5 * PLAYER_SPEED);
                    break;
                case SDLK_LSHIFT:
                    _camera.moveDown(PLAYER_SPEED);
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
        case SDL_KEYUP:
            switch( e->key.keysym.sym ) {
                case SDLK_w:
                case SDLK_s:
                    _scene.player.setZSpeed(0);
                    break;
                case SDLK_a:
                case SDLK_d:
                    _scene.player.setXSpeed(0);
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
            _scene.player.updateDirection(e->motion.xrel, e->motion.yrel);
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