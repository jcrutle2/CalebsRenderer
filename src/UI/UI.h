//
// Created by Caleb Rutledge on 2/3/24.
//

#ifndef OPENGL_TESTS_UI_H
#define OPENGL_TESTS_UI_H

#include <vector>
#include "../Headers/Model.h"
#include "../Headers/Light.h"
#include "imgui/imgui_impl_osx.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace UI {
    void Initalize(SDL_Window * window, void * sdl_gl_context);

    void mainWindow(std::vector<Model> &models, DirectionLight dirLight, std::vector<PointLight> &pointLights, std::string frameRate);
    void modelWindow(Model &model, int num);
    void directionLightWindow(DirectionLight &l);
    void lightWindow(std::vector<PointLight> &lights, int num);
    void newModelWindow(std::vector<Model> &m);

    void renderWindows(std::vector<Model> &models, DirectionLight &dirLight, std::vector<PointLight> &pointLights, std::string frameRate);

    void FrameStart();
    void FrameEnd();
}


#endif //OPENGL_TESTS_UI_H
