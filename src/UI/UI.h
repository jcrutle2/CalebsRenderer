//
// Created by Caleb Rutledge on 2/3/24.
//

#ifndef OPENGL_TESTS_UI_H
#define OPENGL_TESTS_UI_H

#include <vector>
#include "../Headers/Model.h"
#include "imgui/imgui_impl_osx.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

namespace UI {
    void Initalize(SDL_Window * window, void * sdl_gl_context);
    void FrameStart();
    void FrameEnd();
}


#endif //OPENGL_TESTS_UI_H
