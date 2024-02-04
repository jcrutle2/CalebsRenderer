//
// Created by Caleb Rutledge on 12/31/23.
//

#include "Headers/MainGame.h"
#include "imgui_impl_sdl2.h"
#define SPEED 0.5

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to quit...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

MainGame::MainGame() {
    _gameState = GameState::PLAY;
}

MainGame::~MainGame() = default;

void MainGame::run() {
    gameLoop();
    _window.stopSystems();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
        _window.drawBuffered();
    }
}

void MainGame::processInput() {
    SDL_Event e;
    const float speed = 0.025f * _window.getElapsedMS();
    while (SDL_PollEvent(&e)){
        switch (_window.camera.state) {
            case CAMERA_STATE_UNPAUSED:
                processInputUnpaused(&e);
            break;

            case CAMERA_STATE_PAUSED:
                processInputPaused(&e);
            break;
        }
    }
}

void MainGame::processInputUnpaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_KEYDOWN:
            switch( e->key.keysym.sym ) {
                case SDLK_w:
                    _window.camera.moveForward(SPEED);
                    break;
                case SDLK_s:
                    _window.camera.moveBackward(SPEED);
                    break;
                case SDLK_a:
                    _window.camera.moveLeft(SPEED);
                    break;
                case SDLK_d:
                    _window.camera.moveRight(SPEED);
                    break;
                case SDLK_SPACE:
                    _window.camera.moveUp(SPEED);
                    break;
                case SDLK_LSHIFT:
                    _window.camera.moveDown(SPEED);
                    break;
                case SDLK_v:
                    _window.toggleRenderMode();
                    break;
                case SDLK_ESCAPE:
                    _window.camera.toggleCameraState();
                    break;
                case SDLK_q:
                    _gameState = GameState::EXIT;
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            _window.camera.updateDirection(e->motion.xrel, e->motion.yrel);
            break;
        case SDL_MOUSEWHEEL:
            _window.camera.updateZoom(e->wheel.y);
            break;
        default:
            break;
    }
}

void MainGame::processInputPaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (ImGui::GetIO().WantCaptureMouse) {
                ImGui_ImplSDL2_ProcessEvent(e);
            }
            else {
                _window.camera.toggleCameraState();
            }
            break;
        case SDL_KEYDOWN:
            switch( e->key.keysym.sym ) {
                case SDLK_ESCAPE:
                    _window.camera.toggleCameraState();
                    break;

                case SDLK_q:
                    _gameState = GameState::EXIT;
                    break;

                default:
                    ImGui_ImplSDL2_ProcessEvent(e);
                    break;
            }
            break;

        default:
            ImGui_ImplSDL2_ProcessEvent(e);
            break;
    }
}