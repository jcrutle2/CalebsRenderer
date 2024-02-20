//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"
#include "boxMacros.h"


void UI::boxWindow(std::vector<Box> &boxes, int num) {
    ImGui::Begin(boxes[num].name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    auto &box = boxes[num];

    std::string bufferKey = getKey("Box", box.name);
    if (ImGui::CollapsingHeader("Properties")) {
        ImGui::InputText(" ", charBuffers[bufferKey], 32);
        ImGui::SameLine();
        if (ImGui::Button("Save Name")) {
            bool safeToRename = true;
            for (const auto &b : boxes) {
                if (b.name == charBuffers[bufferKey]) {
                    safeToRename = false;
                    break;
                }
            }
            if (safeToRename) {
                std::string oldName = box.getName();
                box.name = charBuffers[bufferKey];
                UI_MAP_CLEANUP("Box", oldName);

                bufferKey = getKey("Box", box.name);
                openWindows[bufferKey] = true;
            }
        }
    }

    if (ImGui::CollapsingHeader("Location")) {
        UI_LOCATION_MENU(box);
    }

    if (ImGui::CollapsingHeader("Geometry")) {
        if (ImGui::TreeNode("Box Vertex List")) {
            glm::vec3 V0 = box.getV0();
            glm::vec3 V1 = box.getV1();
            glm::vec3 V2 = box.getV2();
            glm::vec3 V3 = box.getV3();
            glm::vec3 V4 = box.getV4();
            glm::vec3 V5 = box.getV5();
            glm::vec3 V6 = box.getV6();
            glm::vec3 V7 = box.getV7();
            if (ImGui::InputFloat3("V0", &V0.x)) {
                box.setV0(V0);
            }
            if (ImGui::InputFloat3("V1", &V1.x)) {
                box.setV1(V1);
            }
            if (ImGui::InputFloat3("V2", &V2.x)) {
                box.setV2(V2);
            }
            if (ImGui::InputFloat3("V3", &V3.x)) {
                box.setV3(V3);
            }
            if (ImGui::InputFloat3("V4", &V4.x)) {
                box.setV4(V4);
            }
            if (ImGui::InputFloat3("V5", &V5.x)) {
                box.setV5(V5);
            }
            if (ImGui::InputFloat3("V6", &V6.x)) {
                box.setV6(V6);
            }
            if (ImGui::InputFloat3("V7", &V7.x)) {
                box.setV7(V7);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Additional Geometry")) {
            ImGui::BeginChild("Additional Geometry", ImVec2(250, 100), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
            for (int i = 6; i < box.getTileList().size(); i++) {
                auto &tile = box.getTileList()[i];
                if (ImGui::TreeNode(tile.getName().c_str())) {

                    glm::vec3 V1 = tile.getVert1();
                    glm::vec3 V2 = tile.getVert2();
                    glm::vec3 V3 = tile.getVert3();
                    glm::vec3 V4 = tile.getVert4();
                    ImGui::PushItemWidth(200);
                    if (ImGui::InputFloat3("V1", &V1.x, "%0.2f")) {
                        tile.setVert1(V1);
                    }
                    if (ImGui::InputFloat3("V2", &V2.x, "%0.2f")) {
                        tile.setVert2(V2);
                    }
                    if (ImGui::InputFloat3("V3", &V3.x, "%0.2f")) {
                        tile.setVert3(V3);
                    }
                    if (ImGui::InputFloat3("V4", &V4.x, "%0.2f")) {
                        tile.setVert4(V4);
                    }
                    // TILE_TEXTURE_POSITION_MENU(tile, , , )
                    ImGui::TreePop();
                }
            }
            ImGui::EndChild();

            if (ImGui::Button("Add Wall")) {
                box.pushBack(TILE_SQUARE);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Hide Walls")) {
            std::vector<std::string> boolKeys;
            BOX_SELECTABLE_LIST_SET(box, boolKeys, box.getActive(counter), box.setActive(counter, openWindows[boolKey]));

            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Texture")) {
        std::vector<std::string> boolKeys;
        BOX_SELECTABLE_LIST_NO_SET(box, boolKeys);

        BOX_TEXTURE_MENU(for (int n = 0; n < box.getTileList().size(); n++) {
                            if (openWindows[boolKeys[n]]) {
                                box.setTexture(n, tex.path.data);
                            }
                        },
                         false);

        int check = 0;
        for (int j = 0; j < boolKeys.size(); j++) {
            if (openWindows[boolKeys[j]]) {
                check = j;
                break;
            }
        }
        BOX_TEXTURE_POSITION_MENU(box, for(int n = 0; n < box.getTileList().size(); n++), if(openWindows[boolKeys[n]]), check);
    }

    if(ImGui::MenuItem("Delete")) {
        UI_MAP_CLEANUP("Box", box.getName());
        boxes.erase(boxes.begin() + num);
    }
    if(ImGui::MenuItem("Close")) {
        UI_MAP_CLEANUP("Box", box.getName());
    }

    ImGui::End();
}