//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

void UI::boxWindow(std::vector<Box> &boxes, int num) {
    ImGui::Begin(boxes[num].name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    auto &box = boxes[num];

    std::string bufferKey = "Box_" + box.name;
    ImGui::InputText(" ", charBuffers[bufferKey], 32);
    ImGui::SameLine();
    if (ImGui::Button("Save Name")) {
        box.name = charBuffers[bufferKey];
        charBuffers.erase(bufferKey);
    }

    if (ImGui::CollapsingHeader("Location")) {
        glm::vec3 position = box.getPosition();
        glm::vec3 axis = box.getRotationAxis();
        float rotation = box.getRotation();
        glm::vec3 scale = box.getScale();
        if (ImGui::InputFloat3("Position", &position.x)) {
            box.setPosition(position);
        }
        if (ImGui::InputFloat("Rotation", &rotation)) {
            box.setRotation(rotation);
        }
        if (ImGui::InputFloat3("Axis", &axis.x)) {
            box.setRotationAxis(axis);
        }
        if (ImGui::InputFloat3("Scale", &scale.x)) {
            box.setScale(scale);
        }
    }

    if (ImGui::CollapsingHeader("Geometry")) {
        if (ImGui::TreeNode("Vertex List")) {
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

        if (ImGui::TreeNode("Hide Walls")) {
            if (ImGui::BeginListBox(""))
            {
                for (int tileCounter = 0; tileCounter < box.getTileList().size(); tileCounter++)
                {
                    bool flag = false;
                    if (!box.getActive(tileCounter)) {
                        flag = true;
                        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(0.4f, 0.4f, 0.4f));
                    }

                    if (ImGui::Selectable(box.getTileList()[tileCounter].getName().c_str())) {
                        box.toggleActive(tileCounter);
                    }

                    if (flag) {
                        ImGui::PopStyleColor(1);
                    }
                }
                ImGui::EndListBox();
            }
            if (ImGui::Button("Add Wall")) {
                box.pushBack(TILE_SQUARE);
            }
            ImGui::TreePop();
        }
    }

    if(ImGui::MenuItem("Close")) {
        openBox[num] = false;
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}