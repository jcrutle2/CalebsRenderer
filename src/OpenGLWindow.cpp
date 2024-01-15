//
// Created by Caleb Rutledge on 1/4/24.
//

#include "Headers/OpenGLWindow.h"


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

    _currentFrame = 0;
    _lastFrame = 0;
    _deltaTime = 0;
    _elapsedMS = 0;
    _frameInt = 0;

    camera = Camera();

    initSystems();
}

OpenGLWindow::OpenGLWindow( int screenWidth, int screenHeight) {
    _window = nullptr;
    _context = nullptr;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    camera = Camera();

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

    // initialize default shader
    _shader = Shader("Shaders/exVertex.vert", "Shaders/exFragment.frag");

    // initialize VAO
    glGenVertexArrays(1, &_VAO);

    // initialize buffer
    glGenBuffers(1, &_VBO);

    // initialize EBO
    glGenBuffers(1, &_EBO);

    // initialize container texture;
    newTexture(_texture, "images/container.jpg", "");

    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // trap mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // load backpack model
    _models.push_back(Model("models/cursed.obj"));

    // load lights
    _dirLights.push_back(DirectionLight(glm::vec3(0.2f, -0.2f, -0.1f)));
    _pointLights.push_back(PointLight(glm::vec3(0.0f, 0.0f, -3.0f)));

    // uncomment to test in wireframe mode
    _renderMode = GL_FILL;
    glPolygonMode( GL_FRONT_AND_BACK, _renderMode );

}

void OpenGLWindow::toggleRenderMode() {
    _renderMode = (_renderMode == GL_FILL) ? GL_LINE : GL_FILL;
    glPolygonMode( GL_FRONT_AND_BACK, _renderMode );
}

void OpenGLWindow::stopSystems() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void OpenGLWindow::update() {
    SDL_GL_SwapWindow(_window);
}

void OpenGLWindow::setTriangle() {
    float vertices[] = {
// positions // colors // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    };
   /* unsigned int indices[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };*/

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
/*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
*/
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void OpenGLWindow::drawBuffered() {

    // clear depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // select shaders
    useTexture(_texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.id);
    glBindVertexArray(_VAO);

    //DRAWING CUSTOM MODEL

    // use shader
    _shader.use();

    // set matrices
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0,3,-4));
    _shader.setMats(model, camera.getView(), camera.getPerspective());

    // set directional light
    _shader.setDirectionLight(_dirLights[0]);

    // set point lights
    _shader.setPointLights(_pointLights);

    // send camera position
    _shader.setCamera(camera);

    // draw OpenGL
    _models[0].Draw(_shader);

    update();
    logFrames();
}

void OpenGLWindow::logFrames() {
    _currentFrame = SDL_GetPerformanceCounter();
    _deltaTime = (float) (_currentFrame - _lastFrame) / SDL_GetPerformanceFrequency();
    _elapsedMS = _deltaTime * 1000;
    SDL_Delay(floor(16.666f - _elapsedMS));
    _elapsedMS = std::max(_elapsedMS, 16.666f);
    if (_frameInt >= 60) {
        std::cout << "Current FPS: " <<  std::to_string(1.0f / (_elapsedMS / 1000.0f)) << std::endl;
        _frameInt = 0;
    }
    else _frameInt++;
    _lastFrame = SDL_GetPerformanceCounter();
}

float OpenGLWindow::getElapsedMS() {
    return _elapsedMS;
}