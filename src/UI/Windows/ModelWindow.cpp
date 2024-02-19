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
        model.name = charBuffers[bufferKey];
        openWindows.erase(bufferKey);
        charBuffers.erase(bufferKey);
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

void UI::newModelWindow(std::vector<Model> &m) {
    ImGui::Begin("Add Model", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", modelPath.c_str());

    ImGui::BeginChild("File Paths", ImVec2(175, 100), ImGuiChildFlags_ResizeY |ImGuiChildFlags_Border);
    for (const auto& entry : fs::directory_iterator(modelPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            std::string f = fileExtension(shortPath);
            if (f != ".jpg" && f != ".png") {
                if (ImGui::Selectable(shortPath.c_str())) {
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
    ImGui::EndChild();

    if(ImGui::MenuItem("Back")) {
        UI::back(modelPath);
    }

    if(ImGui::MenuItem("Close")) {
        openLoadModel = false;
    }

    ImGui::End();
}