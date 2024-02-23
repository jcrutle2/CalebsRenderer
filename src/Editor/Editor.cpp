//
// Created by Caleb Rutledge on 12/31/23.
//

#include "Editor.h"
#include "imgui_impl_sdl2.h"
#define PLAYER_SPEED 1.5

Editor::Editor() {
    _gameState = GameState::PLAY;

    _scene = Scene();
    // load lights
    _scene.dirLight = DirectionLight("Direction Light", glm::vec3(0.2f, -0.2f, -0.1f));
    // Test Tiles
    _scene.boxes.emplace_back("Box1", glm::vec3(0.0f,0.0f,0.0f));
}

Editor::~Editor() = default;

void Editor::run() {
    while (_gameState != GameState::EXIT) {
        processInput();

        // Render Geometry and IMGUI
        UI::FrameStart();
        _renderer.draw(_scene, _camera);
        UI::renderWindows(_scene, _camera, _renderer.getFrameRate());
        UI::FrameEnd();

        // Flush to Screen
        _renderer.update();
    }
    _renderer.stopSystems();
}

void Editor::processInput() {
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

void Editor::processInputUnpaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_KEYDOWN:
            switch( e->key.keysym.sym ) {
                case SDLK_w:
                    _camera.moveForward(PLAYER_SPEED);
                    break;
                case SDLK_s:
                    _camera.moveBackward(PLAYER_SPEED);
                    break;
                case SDLK_a:
                    _camera.moveLeft(PLAYER_SPEED);
                    break;
                case SDLK_d:
                    _camera.moveRight(PLAYER_SPEED);
                    break;
                case SDLK_SPACE:
                    _camera.moveUp(PLAYER_SPEED);
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

void Editor::processInputPaused(SDL_Event * e) {
    switch (e->type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (ImGui::GetIO().WantCaptureMouse) {
                ImGui_ImplSDL2_ProcessEvent(e);
            }
            else {
                _camera.toggleCameraState();
            }
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
                    ImGui_ImplSDL2_ProcessEvent(e);
                    break;
            }
            break;

        default:
            ImGui_ImplSDL2_ProcessEvent(e);
            break;
    }
}