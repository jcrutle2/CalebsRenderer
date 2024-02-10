//
// Created by Caleb Rutledge on 2/3/24.
//
#pragma once

#ifndef OPENGL_TESTS_UI_H
#define OPENGL_TESTS_UI_H

#include <vector>
#include "../Rendering/Models/Model.h"
#include "../Rendering/Light/Light.h"
#include "imgui/imgui_impl_osx.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "../Scene/SceneLoader.h"
#include <filesystem>
namespace fs = std::filesystem;

extern bool my_tool_active;

namespace UI {
    void Initalize(SDL_Window * window, void * sdl_gl_context);

    void mainWindow(Scene &s, Camera &c, const std::string &frameRate);
    void modelWindow(Model &model, int num);
    void directionLightWindow(DirectionLight &l);
    void lightWindow(std::vector<PointLight> &lights, int num);
    void newModelWindow(std::vector<Model> &m);
    void loadSceneWindow(Scene &s);

    void renderWindows(Scene &s, Camera &c, const std::string &frameRate);

    void FrameStart();
    void FrameEnd();

    void back(std::string &s);
    std::string shorten(const std::string &s);

    // extern globals
    extern std::unordered_map<int, bool> openModels;
    extern bool addModelWindow;
    extern bool openDirLight;
    extern std::unordered_map<int, bool> openLights;
    extern bool openLoadModel;
    extern std::string filePath ;
    extern std::string path;
    extern std::string scenesPath;
    extern char nameBuf[32];
    extern char sceneBuf[64];
}


#endif //OPENGL_TESTS_UI_H
