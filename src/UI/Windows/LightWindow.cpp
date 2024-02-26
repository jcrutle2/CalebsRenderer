//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"
#include "LightMacros.h"
#include "../UIMacros.h"

void UI::directionLightWindow(DirectionLight &l) {
    ImGui::Begin("Direction Light", &my_tool_active, ImGuiWindowFlags_MenuBar);

    DIRECTION_LIGHT_WINDOW(l);
    if(ImGui::MenuItem("Close")) {
        openWindows[getKey("Light", "Direction Light")] = false;
    }

    ImGui::End();
}

void UI::lightWindow(std::vector<PointLight> &lights, int num) {

    PointLight &l = lights[num];
    std::string name = l.getName();
    std::string bufferKey = getKey("Light", name);

    ImGui::Begin(name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    UI_SAFE_RENAME(l, lights, "Light");

    POINT_LIGHT_WINDOW(l);

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