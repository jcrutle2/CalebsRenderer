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
    _window.setTriangle();
    gameLoop();
    _window.stopSystems();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
        _window.drawBuffered(_camera.getView(), _camera.getPerspective());
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
                        _camera.moveForward(speed);
                        break;
                    case SDLK_s:
                        _camera.moveBackward(speed);
                        break;
                    case SDLK_a:
                        _camera.moveLeft(speed);
                        break;
                    case SDLK_d:
                        _camera.moveRight(speed);
                        break;
                    case SDLK_SPACE:
                        _camera.moveUp(speed);
                        break;
                    case SDLK_LSHIFT:
                        _camera.moveDown(speed);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                _camera.updateDirection(e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                _camera.updateZoom(e.wheel.y);
                break;
            default:
                break;
        }
    }
}