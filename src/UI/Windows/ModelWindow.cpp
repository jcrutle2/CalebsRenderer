//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"
#include "../UIMacros.h"
#include "LightMacros.h"
#include "ModelMacros.h"

void UI::entityWindow(std::vector<Entity> &e, int num) {
    Entity &entity = e[num];
    ImGui::Begin(entity.getName().c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    std::string bufferKey = getKey("Entity", entity.getName());
    if (ImGui::CollapsingHeader("Properties"))
        UI_SAFE_RENAME(entity, e, "Entity");

    if (ImGui::CollapsingHeader("Location"))
        UI_LOCATION_MENU(entity);

    if (ImGui::CollapsingHeader("Lights")) {
        std::vector<std::string> boolKeys;
        MODEL_LIGHT_SELECTABLE_LIST(entity);
        MODEL_LIGHT_WINDOW_MULTIPLE(entity, boolKeys);
    }

    if(ImGui::MenuItem("Delete")) {
        e.erase(e.begin() + num);
        openWindows.erase(bufferKey);
        charBuffers.erase(bufferKey);
    }
    if(ImGui::MenuItem("Close")) {
        openWindows[bufferKey] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}