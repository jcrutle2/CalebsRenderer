//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::changeSkyboxWindow(Skybox &s) {
    ImGui::Begin("Change Skybox", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", scenesPath.c_str());

    for (const auto& entry : fs::directory_iterator(skyboxPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            if (ImGui::Button(shortPath.substr(1, shortPath.length() - 1).c_str())) {
                std::string skyboxDirectory = "Assets/Skyboxes" + shortPath;
                s.loadSkybox(skyboxDirectory);
                openChangeSkybox = false;
            }
        }
    }

    if(ImGui::MenuItem("Close")) {
        openChangeSkybox = false;
    }

    ImGui::End();
}