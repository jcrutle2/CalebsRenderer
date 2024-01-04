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
    _window = nullptr;
    _context = nullptr;

    _screenWidth = 1024;
    _screenHeight = 768;

    _gameState = GameState::PLAY;
    _shader = Shader();
    _texture = Texture();

    _VAO = 0;
    _VBO = 0;
    _EBO = 0;

    _currentFrame = 0;
    _lastFrame = 0;
    _deltaTime = 0;
    _elapsedMS = 0;
    _frameInt = 0;
}

MainGame::~MainGame() = default;

void MainGame::run() {
    initSystems();
    setTriangle();
    gameLoop();
    stopSystems();
}

void MainGame::initSystems() {
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
        fatalError("Error: SDL Window could not be created.");
    }

    _context = SDL_GL_CreateContext(_window);

    if (_context == nullptr) {
        fatalError("Error: GL Context could not be created.");
    }

    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        fatalError("Error: Failed to initialize GLEW!");
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

    // initialiaze container texture;
    _texture = Texture("images/container.jpg");

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // initialize camera
    _camera = Camera();

    // trap mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void MainGame::stopSystems() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {

        processInput();
        drawGame();

        // fps timer
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
}

void MainGame::processInput() {
    SDL_Event e;
    const float speed = 0.025f * _elapsedMS;
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

void MainGame::drawGame() {
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw triangle
    drawBuffered();
}

void MainGame::setTriangle() {
    float vertices[] = {
// positions // colors // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
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
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
    unsigned int indices[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void MainGame::drawBuffered() {

    // clear depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // positions of 10 cubes
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f, 0.0f, 0.0f),
            glm::vec3( 2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f, 2.0f, -2.5f),
            glm::vec3( 1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // select shaders
    _texture.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.ID);
    glBindVertexArray(_VAO);

    glm::mat4 view = _camera.getView();
    glm::mat4 projection = _camera.getPerspective();

    for (unsigned int i = 0; i < 10; i++) {
        // set model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        float speed = 0.1 * i;
        model = glm::rotate(model, glm::radians(angle),
                            glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::rotate(model, (float) (SDL_GetTicks64() / 200.0) * glm::radians(55.0f), glm::vec3(speed,0.3f,0.0f));

        // apply perspective matrices
        GLint modelLoc = glGetUniformLocation(_shader.ID, "model");
        GLint viewLoc = glGetUniformLocation(_shader.ID, "view");
        GLint projectionLoc = glGetUniformLocation(_shader.ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        _shader.use(); // don’t forget to activate the shader first!
        glUniform1i(glGetUniformLocation(_shader.ID, "texture1"), 0); // manually

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // draw OpenGL
    SDL_GL_SwapWindow(_window);


}