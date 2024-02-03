//
// Created by Caleb Rutledge on 2/3/24.
//

#include "UI.h"

bool my_tool_active = true;

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

void UI::FrameStart() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)
}

void UI::FrameEnd() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}