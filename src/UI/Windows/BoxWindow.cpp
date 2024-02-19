//
// Created by Caleb Rutledge on 2/18/24.
//

#include "../UI.h"

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
                box.name = charBuffers[bufferKey];
                charBuffers.erase(bufferKey);
                openWindows.erase(bufferKey);
            }
        }
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

                    float texRot = tile.getTextureRotation();
                    if (ImGui::InputFloat("Texture Rotation", &texRot, 5.0f, 10.0f, "%0.1f"))
                        tile.setTextureRotation(texRot);

                    float texScale = tile.getTextureScale();
                    if (ImGui::InputFloat("Texture Scale", &texScale, 0.25f, 1.0f, "%0.3f"))
                        tile.setTextureScale(texScale);
                    ImGui::PopItemWidth();

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
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Texture")) {
        if (ImGui::TreeNode("Change Box Texture")) {
            ImGui::BeginChild("Textures", ImVec2(250, 80), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
            for (int i = 0; i < TextureGlobals::loaded.size(); i++) {
                const auto &tex = TextureGlobals::loaded[i];
                if (ImGui::ImageButton((void *) (intptr_t) tex.id, ImVec2(42, 42))) {
                    box.setBoxTextures(tex.path.data);
                }
                if ((i != (TextureGlobals::loaded.size() - 1) && ((i + 1) % 4))) {
                    ImGui::SameLine();
                }
            }
            ImGui::EndChild();

            ImGui::PushItemWidth(136);
            float texRot = box.getTextureRotation(0);
            if (ImGui::InputFloat("Texture Rotation", &texRot, 5.0f, 10.0f, "%0.1f"))
                box.setBoxTextureRotation(texRot);
            float texScale = box.getTextureScale(0);
            if (ImGui::InputFloat("Texture Scale", &texScale, 0.25f, 1.0f, "%0.3f"))
                box.setBoxTextureScale(texScale);
            glm::vec2 texPosition = box.getTexturePosition(0);
            if (ImGui::InputFloat2("Texture Position", &texPosition.x, "%0.3f"))
                box.setBoxTexturePosition(texPosition);
            ImGui::PopItemWidth();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Change All Textures")) {
            ImGui::BeginChild("Textures", ImVec2(250, 80), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
            for (int i = 0; i < TextureGlobals::loaded.size(); i++) {
                const auto &tex = TextureGlobals::loaded[i];

                std::string windowKey = "All_Change_";
                windowKey += tex.path.data;
                if (ImGui::ImageButton((void *) (intptr_t) tex.id, ImVec2(42, 42))) {
                    ImGui::OpenPopup(windowKey.c_str());
                }
                // Always center this window when appearing
                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

                if (ImGui::BeginPopupModal(windowKey.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ImGui::Text("Are you sure you want to change all textures of this box?");
                    ImGui::Separator();

                    if (ImGui::Button("Yes", ImVec2(120, 0))) {
                        box.setAllTextures(tex.path.data);
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SetItemDefaultFocus();
                    ImGui::SameLine();
                    if (ImGui::Button("No", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                    ImGui::EndPopup();
                }

                if ((i != (TextureGlobals::loaded.size() - 1) && ((i + 1) % 4))) {
                    ImGui::SameLine();
                }
            }
            ImGui::EndChild();

            ImGui::PushItemWidth(136);
            float texRot = box.getTextureRotation(0);
            if (ImGui::InputFloat("Texture Rotation", &texRot, 5.0f, 10.0f, "%0.1f"))
                box.setAllTextureRotation(texRot);
            float texScale = box.getTextureScale(0);
            if (ImGui::InputFloat("Texture Scale", &texScale, 0.25f, 1.0f, "%0.3f"))
                box.setAllTextureScale(texScale);
            glm::vec2 texPosition = box.getTexturePosition(0);
            if (ImGui::InputFloat2("Texture Position", &texPosition.x, "%0.3f"))
                box.setAllTexturePosition(texPosition);
            ImGui::PopItemWidth();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Change Individual Textures")) {
            ImGui::BeginChild("Individual Textures", ImVec2(250, 300), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);

            for (int i = 0; i < box.getTileList().size(); i++) {
                auto &tile = box.getTileList()[i];

                if (ImGui::TreeNode(tile.getName().c_str())) {
                    ImGui::BeginChild("Textures", ImVec2(200, 100), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);
                    for (int j = 0; j < TextureGlobals::loaded.size(); j++) {
                        const auto &tex = TextureGlobals::loaded[j];
                        if (ImGui::ImageButton((void *) (intptr_t) tex.id, ImVec2(42, 42))) {
                            box.setTexture(i, tex.path.data);
                        }
                        if ((j != (TextureGlobals::loaded.size() - 1) && ((j + 1) % 3))) {
                            ImGui::SameLine();
                        }
                    }
                    ImGui::EndChild();

                    ImGui::PushItemWidth(90);
                    float texRot = box.getTextureRotation(0);
                    if (ImGui::InputFloat("Texture Rotation", &texRot, 5.0f, 10.0f, "%0.1f"))
                        box.setTextureRotation(i, texRot);
                    float texScale = box.getTextureScale(0);
                    if (ImGui::InputFloat("Texture Scale", &texScale, 0.25f, 1.0f, "%0.3f"))
                        box.setTextureScale(i, texScale);
                    glm::vec2 texPosition = box.getTexturePosition(0);
                    if (ImGui::InputFloat2("Texture Position", &texPosition.x, "%0.3f"))
                        box.setTexturePosition(i, texPosition);
                    ImGui::PopItemWidth();

                    ImGui::TreePop();
                }
            }

            ImGui::EndChild();
            ImGui::TreePop();
        }
    }

    if(ImGui::MenuItem("Delete")) {
        boxes.erase(boxes.begin() + num);
        openWindows.erase(bufferKey);
        charBuffers.erase(bufferKey);
    }
    if(ImGui::MenuItem("Close")) {
        charBuffers.erase(bufferKey);
    }

    ImGui::End();
}