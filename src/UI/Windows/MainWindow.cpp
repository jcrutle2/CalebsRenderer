//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::mainWindow(Scene &s, Camera &c, const std::string &frameRate) {

    if (ImGui::CollapsingHeader("Info")) {
        ImGui::Text("%s", ("Frame Rate: " + frameRate).c_str());
        ImGui::InputFloat3("Camera", &c.cameraPos.x);
    }

    if (ImGui::CollapsingHeader("Boxes")) {
        int boxCount = 0;
        ImGui::BeginChild("Boxes", ImVec2(175, 100), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
        for (auto const &b: s.boxes) {
            if (ImGui::Selectable(b.name.c_str())) {
                openWindows[getKey("Box", b.name)] = true;
            }
            boxCount++;
        }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("Boxes Options", ImVec2(125, 100),  ImGuiChildFlags_ResizeY);
        if (ImGui::Button("Add Box")) {
            std::string name = "Box" + std::to_string(s.boxes.size() + 1);

            for (int i = 0; i < s.boxes.size(); i++) {
                if (s.boxes[i].name == name) {
                    name += "*";
                    i = 0;
                }
            }

            s.boxes.emplace_back(name, glm::vec3(0.0f, 0.0f, 0.0f));
        }
        ImGui::EndChild();
    }

    if (ImGui::CollapsingHeader("Models")) {
        int modelCount = 0;
        ImGui::BeginChild("Models", ImVec2(175, 100), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
            for (auto const &m : s.models) {
                if (ImGui::Selectable(m.name.c_str())) {
                    openWindows[getKey("Model", m.name)] = true;
                }
                modelCount++;
            }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("Model Options", ImVec2(125, 100), ImGuiChildFlags_ResizeY);
            if (ImGui::Button("Add Model")) {
                openLoadModel = true;
            }
        ImGui::EndChild();
    }


    if (ImGui::CollapsingHeader("Environment")) {
        ImGui::BeginChild("Lights", ImVec2(175, 100), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
            if (ImGui::Selectable("Direction Light")) {
                openWindows[getKey("Light", "Direction Light")] = true;
            }
            for (int i = 0; i < s.pointLights.size(); i++) {
                std::string n = s.pointLights[i].name;
                if (ImGui::Selectable(n.c_str())) {
                    openWindows[getKey("Light", n)] = true;
                }
            }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("Lights Options", ImVec2(125, 100), ImGuiChildFlags_ResizeY);
            if (ImGui::Button("Add Light")) {
                std::string name = "Light" + std::to_string(s.pointLights.size() + 1);
                s.pointLights.emplace_back(name);
            }
            if (ImGui::Button("Change Skybox")) {
                openChangeSkybox = true;
            }
        ImGui::EndChild();
    }

    if (ImGui::CollapsingHeader("Scene")) {
        std::string bufferKey = "Scene_Buf";
        ImGui::InputText("Name", charBuffers[bufferKey], 64);
        if (ImGui::Button("Save Scene")) {
            std::string savePath = "Assets/Scenes/";
            savePath += (strcmp(charBuffers[bufferKey], "")) ? charBuffers[bufferKey] : "scene";
            savePath += ".bin";
            SceneLoader::storeScene(s, savePath);
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Scene")) {
            openLoadScene = true;
        }
    }
}