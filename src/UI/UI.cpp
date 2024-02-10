//
// Created by Caleb Rutledge on 2/3/24.
//

#include "UI.h"
#include <algorithm>



void UI::Initalize(SDL_Window * window, void * sdl_gl_context) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    if (io.BackendPlatformUserData == nullptr) {
        ImGui_ImplSDL2_InitForOpenGL(window, sdl_gl_context);
        ImGui_ImplOpenGL3_Init();
    }
}

void UI::renderWindows(Scene &s, const std::string &frameRate) {
    mainWindow(s, frameRate);

    int modelCount = 0;
    for (auto &model : s.models) {
        if (openModels[modelCount]) modelWindow(model, modelCount);
        modelCount++;
    }

    if (openDirLight) directionLightWindow(s.dirLight);

    int lightCount = 0;
    for (auto &light : s.pointLights) {
        if (openLights[lightCount]) lightWindow(s.pointLights, lightCount);
        lightCount++;
    }

    if (addModelWindow) newModelWindow(s.models);
    else path = filePath;

    if (openLoadModel) loadSceneWindow(s);
}