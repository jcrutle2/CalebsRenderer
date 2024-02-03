//
// Created by Caleb Rutledge on 12/31/23.
//

#include "Headers/MainGame.h"

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to quit...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

MainGame::MainGame() {
    _window = OpenGLWindow();

    _gameState = GameState::PLAY;
    _camera = Camera();

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
        switch (e.type) {
            case SDL_QUIT:
            case SDL_MOUSEBUTTONDOWN:
                _gameState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                switch( e.key.keysym.sym ) {
                    case SDLK_w:
                        _window.camera.moveForward(speed);
                        break;
                    case SDLK_s:
                        _window.camera.moveBackward(speed);
                        break;
                    case SDLK_a:
                        _window.camera.moveLeft(speed);
                        break;
                    case SDLK_d:
                        _window.camera.moveRight(speed);
                        break;
                    case SDLK_SPACE:
                        _window.camera.moveUp(speed);
                        break;
                    case SDLK_LSHIFT:
                        _window.camera.moveDown(speed);
                        break;
                    case SDLK_v:
                        _window.toggleRenderMode();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                _window.camera.updateDirection(e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                _window.camera.updateZoom(e.wheel.y);
                break;
            default:
                break;
        }
    }
}