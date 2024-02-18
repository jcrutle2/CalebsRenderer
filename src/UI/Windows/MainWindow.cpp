//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::mainWindow(Scene &s, Camera &c, const std::string &frameRate) {
    ImGui::Text("%s", ("Frame Rate: " + frameRate).c_str());
    ImGui::InputFloat3("Camera", &c.cameraPos.x);

    if (ImGui::CollapsingHeader("Models")) {
        int modelCount = 0;
        if (ImGui::BeginListBox(" ")) {
            for (auto const &m : s.models) {
                if (ImGui::Selectable(m.name.c_str())) {
                    openModels[modelCount] = true;
                }
                modelCount++;
            }
            ImGui::EndListBox();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Model")) {
            openLoadModel = true;
        }
    }


    if (ImGui::CollapsingHeader("Environment")) {
        ImGui::Text("\nLight List");
        if (ImGui::Button("Direction Light")) {
            openDirLight = true;
        }
        for (int i = 0; i < s.pointLights.size(); i++) {
            std::string n = s.pointLights[i].name;
            if (ImGui::Button(n.c_str())) {
                openLights[i] = true;
            }
        }
        if (ImGui::Button("Add Light")) {
            std::string name = "Light" + std::to_string(s.pointLights.size() + 1);
            s.pointLights.emplace_back(name);
        }

        ImGui::Text("\nSkybox");
        if (ImGui::Button("Change Skybox")) {
            openChangeSkybox = true;
        }
    }

    if (ImGui::CollapsingHeader("Boxes")) {
        int boxCount = 0;
        if (ImGui::BeginListBox(" ")) {
            for (auto const &b: s.boxes) {
                if (ImGui::Selectable(b.name.c_str())) {
                    openBox[boxCount] = true;
                }
                boxCount++;
            }
            ImGui::EndListBox();
        }
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