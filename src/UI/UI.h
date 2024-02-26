//
// Created by Caleb Rutledge on 2/3/24.
//
#pragma once

#ifndef OPENGL_TESTS_UI_H
#define OPENGL_TESTS_UI_H

#include <vector>
#include "../Geometry/Models/Model.h"
#include "../Environment/Light/Light.h"
#include "imgui/imgui_impl_osx.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "../Scene/Scene.h"
#include <filesystem>
namespace fs = std::__fs::filesystem;

extern bool my_tool_active;

namespace UI {
    void Initalize(SDL_Window * window, void * sdl_gl_context);

    void mainWindow(Scene &s, Camera &c, const std::string &frameRate);
    void modelWindow(std::vector<Entity> &m, int num);
    void directionLightWindow(DirectionLight &l);
    void lightWindow(std::vector<PointLight> &lights, int num);
    void boxWindow(std::vector<Box> &boxes, int num);
    void loadSceneWindow(Scene &s);
    void changeSkyboxWindow(Skybox &s);

    void renderWindows(Scene &s, Camera &c, const std::string &frameRate);

    void FrameStart();
    void FrameEnd();

    void back(std::string &s);
    std::string shorten(const std::string &s);
    std::string fileExtension(const std::string &s);
    std::string getKey(const std::string &type, const std::string &name, const std::string &sub = "", const std::string &sub2 = "");
    std::string getKeyType(const std::string &key);
    std::string getKeyName(const std::string &key);
    std::string getKeySubType(const std::string &key);
    std::string getKeySubSubType(const std::string &key);

    // extern globals
    extern std::unordered_map<std::string, bool> openWindows;
    extern std::unordered_map<std::string, char[32]> charBuffers;
    extern bool openLoadScene;
    extern bool openChangeSkybox;
    extern std::string filePath;
    extern std::string modelPath;
    extern std::string scenesPath;
    extern std::string skyboxPath;
}


#endif //OPENGL_TESTS_UI_H
