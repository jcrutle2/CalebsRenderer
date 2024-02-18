//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::loadSceneWindow(Scene &s) {
    ImGui::Begin("Load Scene", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", scenesPath.c_str());

    for (const auto& entry : fs::directory_iterator(scenesPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            if (ImGui::Button(shortPath.c_str())) {
                std::string getScenePath = "Assets/Scenes";
                getScenePath += shortPath;
                s = SceneLoader::getSceneFromDisk(getScenePath);
                openLoadScene = false;
            }
        }
    }

    if(ImGui::MenuItem("Close")) {
        openLoadScene = false;
    }

    ImGui::End();
}