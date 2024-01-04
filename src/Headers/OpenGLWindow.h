//
// Created by Caleb Rutledge on 1/4/24.
//

#ifndef OPENGL_TESTS_OPENGLWINDOW_H
#define OPENGL_TESTS_OPENGLWINDOW_H

#include "SDL.h"
#include "glew.h"

class OpenGLWindow {
    public:
        OpenGLWindow();
        OpenGLWindow(int screenWidth, int screenHeight);
        ~OpenGLWindow();
        void initSystems();

    private:
        SDL_Window* _window;
        SDL_GLContext _context;

        int _screenWidth;
        int _screenHeight;
};


#endif //OPENGL_TESTS_OPENGLWINDOW_H
