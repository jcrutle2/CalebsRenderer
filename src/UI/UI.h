//
// Created by Caleb Rutledge on 2/3/24.
//
#pragma once

#ifndef OPENGL_TESTS_UI_H
#define OPENGL_TESTS_UI_H

#include <vector>
#include "../Geometry//Models/Model.h"
#include "../Environment/Light/Light.h"
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
    void modelWindow(std::vector<Model> &m, int num);
    void directionLightWindow(DirectionLight &l);
    void lightWindow(std::vector<PointLight> &lights, int num);
    void newModelWindow(std::vector<Model> &m);
    void loadSceneWindow(Scene &s);
    void changeSkyboxWindow(Skybox &s);

    void renderWindows(Scene &s, Camera &c, const std::string &frameRate);

    void FrameStart();
    void FrameEnd();

    void back(std::string &s);
    std::string shorten(const std::string &s);
    std::string fileExtension(const std::string &s);

    // extern globals
    extern std::unordered_map<int, bool> openModels;
    extern std::unordered_map<int, bool> openLights;
    extern bool openLoadModel;
    extern bool openDirLight;
    extern bool openLoadScene;
    extern bool openChangeSkybox;
    extern std::string filePath;
    extern std::string modelPath;
    extern std::string scenesPath;
    extern std::string skyboxPath;
    extern char nameBuf[32];
    extern char sceneBuf[64];
    extern char lightBuf[32];
}


#endif //OPENGL_TESTS_UI_H
