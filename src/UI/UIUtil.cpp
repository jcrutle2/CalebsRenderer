//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

void UI::back(std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '/') {
            s = s.substr(0, i);
            return;
        }
    }
}

std::string UI::shorten(const std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '/') {
            return s.substr(i, s.length() - i);
        }
    }
    return "";
}

std::string UI::fileExtension(const std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '.') {
            return s.substr(i, s.length() - i);
        }
    }
    return "";
}

void UI::FrameStart() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UI::FrameEnd() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}