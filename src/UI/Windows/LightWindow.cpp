//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::directionLightWindow(DirectionLight &l) {
    ImGui::Begin("Direction Light", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputFloat3("Direction", &l.direction.x);
    ImGui::InputFloat3("Ambient", &l.ambient.x);
    ImGui::InputFloat3("Specular", &l.specular.x);
    ImGui::InputFloat3("Diffuse", &l.diffuse.x);
    if(ImGui::MenuItem("Close")) {
        openDirLight = false;
    }

    ImGui::End();
}

void UI::lightWindow(std::vector<PointLight> &lights, int num) {
    std::string name = lights[num].name;
    PointLight &l = lights[num];
    ImGui::Begin(name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    std::string bufferKey = "Light_" + l.name;
    ImGui::InputText("Name", charBuffers[bufferKey], 32);
    if (ImGui::Button("Save Name")) {
        if (strcmp(charBuffers[bufferKey], "") != 0) {
            l.name = charBuffers[bufferKey];
            charBuffers.erase(bufferKey);
        }
    }

    ImGui::InputFloat3("Position", &l.position.x);
    ImGui::InputFloat3("Ambient", &l.ambient.x);
    ImGui::InputFloat3("Specular", &l.specular.x);
    ImGui::InputFloat3("Diffuse", &l.diffuse.x);
    ImGui::InputFloat("Constant Falloff", &l.constant);
    ImGui::InputFloat("Linear Falloff", &l.linear);
    ImGui::InputFloat("Quadratic Falloff", &l.quadratic);


    if(ImGui::MenuItem("Delete")) {
        for (auto x : openLights) {
            x.second = false;
        }
        lights.erase(lights.begin() + num);
    }
    if(ImGui::MenuItem("Close")) {
        openLights[num] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}