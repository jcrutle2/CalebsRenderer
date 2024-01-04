//
// Created by Caleb Rutledge on 1/4/24.
//

#include "Headers/OpenGLWindow.h"
#include <iostream>

void sdlFatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to quit...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

OpenGLWindow::OpenGLWindow() {
    _window = nullptr;
    _context = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    initSystems();
}

OpenGLWindow::OpenGLWindow( int screenWidth, int screenHeight) {
    _window = nullptr;
    _context = nullptr;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    initSystems();
}

OpenGLWindow::~OpenGLWindow() = default;

void OpenGLWindow::initSystems() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Set GL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // create window
    _window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

    if (_window == nullptr) {
        sdlFatalError("Error: SDL Window could not be created.");
    }

    _context = SDL_GL_CreateContext(_window);

    if (_context == nullptr) {
        sdlFatalError("Error: GL Context could not be created.");
    }

    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        sdlFatalError("Error: Failed to initialize GLEW!");
    }

    glViewport(0, 0, _screenWidth, _screenHeight);
}