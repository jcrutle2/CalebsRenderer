//
// Created by Caleb Rutledge on 2/3/24.
//

#include "UI.h"

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

void UI::renderWindows(Scene &s, Camera &c, const std::string &frameRate) {
    mainWindow(s, c, frameRate);

    int modelCount = 0;
    for (auto &model : s.models) {
        if (openModels[modelCount]) modelWindow(s.models, modelCount);
        modelCount++;
    }

    if (openDirLight) directionLightWindow(s.dirLight);

    for (int lightCount = 0; lightCount < s.pointLights.size(); lightCount++) {
        if (openLights[lightCount]) lightWindow(s.pointLights, lightCount);
    }

    for (int boxCount = 0; boxCount < s.boxes.size(); boxCount++) {
        if (openBox[boxCount]) {
            boxWindow(s.boxes, boxCount);
        }
    }

    if (openLoadModel) newModelWindow(s.models);
    else modelPath = filePath + + "/Assets/Models";

    if (openLoadScene) loadSceneWindow(s);

    if (openChangeSkybox) changeSkyboxWindow(s.skybox);
}