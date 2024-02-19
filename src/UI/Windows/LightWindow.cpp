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
        openWindows[getKey("Light", "Direction Light")] = false;
    }

    ImGui::End();
}

void UI::lightWindow(std::vector<PointLight> &lights, int num) {

    PointLight &l = lights[num];
    std::string name = l.name;
    std::string bufferKey = getKey("Light", name);

    ImGui::Begin(name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputText("Name", charBuffers[bufferKey], 32);
    if (ImGui::Button("Save Name")) {
        if (strcmp(charBuffers[bufferKey], "") != 0) {
            l.name = charBuffers[bufferKey];
            charBuffers.erase(bufferKey);
            openWindows.erase(bufferKey);
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
        lights.erase(lights.begin() + num);
        openWindows.erase(bufferKey);
        charBuffers.erase(bufferKey);
    }
    if(ImGui::MenuItem("Close")) {
        openWindows[bufferKey] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}