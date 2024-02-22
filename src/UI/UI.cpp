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


    for (int modelCount = 0; modelCount < s.entities.size(); modelCount++) {
        if (openWindows[getKey("Model", s.entities[modelCount].name)])
            modelWindow(s.entities, modelCount);
        if (s.entities[modelCount].lights.empty()) {

        }
    }

    if (openWindows[getKey("Light", "Direction Light")]) directionLightWindow(s.dirLight);

    for (int lightCount = 0; lightCount < s.pointLights.size(); lightCount++) {
        if (openWindows[getKey("Light", s.pointLights[lightCount].name)])
            lightWindow(s.pointLights, lightCount);
    }

    for (int boxCount = 0; boxCount < s.boxes.size(); boxCount++) {
        if (openWindows[getKey("Box", s.boxes[boxCount].getName())]) {
            boxWindow(s.boxes, boxCount);
        }
    }

    if (openLoadScene) loadSceneWindow(s);

    if (openChangeSkybox) changeSkyboxWindow(s.skybox);

    //ImGui::ShowDemoWindow();
}