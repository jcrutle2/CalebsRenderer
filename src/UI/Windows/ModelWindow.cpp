//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::modelWindow(std::vector<Model> &m, int num) {
    Model &model = m[num];
    ImGui::Begin(model.name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    std::string bufferKey = getKey("Model", model.name);
    ImGui::InputText("Name", charBuffers[bufferKey], 32);
    if (ImGui::Button("Save Name")) {
        bool safeToRename = true;
        for (const auto &oM : m) {
            if (oM.name == charBuffers[bufferKey]) {
                safeToRename = false;
                break;
            }
        }
        if (safeToRename) {
            model.name = charBuffers[bufferKey];
            openWindows.erase(bufferKey);
            charBuffers.erase(bufferKey);
        }
    }

    ImGui::InputFloat3("Position", &model.position.x);
    ImGui::InputFloat("Rotation", &model.rotation);
    ImGui::InputFloat3("Axis", &model.rotationAxis.x);
    ImGui::InputFloat3("Scale", &m[num].scale.x);

    ImGui::Text("\nLight List");
    for (int i = 0; i < model.lights.size(); i++) {
        std::string n = model.lights[i].name;
        if (ImGui::Button(n.c_str())) {
            std::cout << "Error: Not yet Implemented";
        }
    }
    if (ImGui::Button("Add Light")) {
        std::string name = "Light" + std::to_string(model.lights.size() + 1);
        model.lights.emplace_back(name);
    }

    if(ImGui::MenuItem("Delete")) {
        m.erase(m.begin() + num);
        openWindows.erase(bufferKey);
        charBuffers.erase(bufferKey);
    }
    if(ImGui::MenuItem("Close")) {
        openWindows[bufferKey] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}