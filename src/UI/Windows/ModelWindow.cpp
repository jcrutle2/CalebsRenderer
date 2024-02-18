//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::modelWindow(std::vector<Model> &m, int num) {
    ImGui::Begin(m[num].name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    std::string bufferKey = "Model_" + m[num].name;
    ImGui::InputText("Name", charBuffers[bufferKey], 32);
    if (ImGui::Button("Save Name")) {
        m[num].name = charBuffers[bufferKey];
        charBuffers.erase(bufferKey);
    }

    ImGui::InputFloat3("Position", &m[num].position.x);
    ImGui::InputFloat("Rotation", &m[num].rotation);
    ImGui::InputFloat3("Axis", &m[num].rotationAxis.x);
    ImGui::InputFloat3("Scale", &m[num].scale.x);

    ImGui::Text("\nLight List");
    for (int i = 0; i < m[num].lights.size(); i++) {
        std::string n = m[num].lights[i].name;
        if (ImGui::Button(n.c_str())) {
            openLights[i] = true;
        }
    }
    if (ImGui::Button("Add Light")) {
        std::string name = "Light" + std::to_string(m[num].lights.size() + 1);
        m[num].lights.emplace_back(name);
    }

    if(ImGui::MenuItem("Delete")) {
        for (auto x : openModels) {
            x.second = false;
        }
        m.erase(m.begin() + num);
    }
    if(ImGui::MenuItem("Close")) {
        openModels[num] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}

void UI::newModelWindow(std::vector<Model> &m) {
    ImGui::Begin("Add Model", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", modelPath.c_str());

    for (const auto& entry : fs::directory_iterator(modelPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            std::string f = fileExtension(shortPath);
            if (f != ".jpg" && f != ".png") {
                if (ImGui::Button(shortPath.c_str())) {
                    if (fs::is_directory(entry))
                        modelPath = entry.path();
                    else {
                        m.emplace_back(Model(shortPath.substr(1, shortPath.length() - 1), static_cast<std::string>(entry.path())));
                        openLoadModel = false;
                    }
                }
            }
        }
    }

    if(ImGui::MenuItem("Back")) {
        UI::back(modelPath);
    }

    if(ImGui::MenuItem("Close")) {
        openLoadModel = false;
    }

    ImGui::End();
}