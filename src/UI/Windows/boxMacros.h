//
// Created by Caleb Rutledge on 2/19/24.
//

#ifndef CALEBSRENDERER_BOXMACROS_H
#define CALEBSRENDERER_BOXMACROS_H

#include "../UIMacros.h"

#define BOX_TEXTURE_MENU(response, warning) {\
    ImGui::BeginChild("Textures", ImVec2(250, 80), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);   \
    for (int j = 0; j < TextureGlobals::loaded.size(); j++) {                                           \
        const auto &tex = TextureGlobals::loaded[j];                                                    \
        if (ImGui::ImageButton((void *) (intptr_t) tex.id, ImVec2(32, 32))) {                           \
            if (warning) {                                                                              \
                std::string windowKey = "All_Change_";                                                  \
                windowKey += tex.path.data;                                                             \
                ImGui::OpenPopup(windowKey.c_str());                                                    \
            }                                                                                           \
            else                                                                                        \
                response;                                                                               \
        }                                                                                               \
        ImGui::SetItemTooltip("%s", shorten(tex.path.data).substr(1).c_str());                          \
        if (warning) {                                                                                  \
            std::string windowKey = "All_Change_";                                                      \
            windowKey += tex.path.data;                                                                 \
            if (ImGui::BeginPopupModal(windowKey.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))     \
            {                                                                                           \
                ImGui::Text("Are you sure you want to change all textures of this box?");               \
                ImGui::Separator();                                                                     \
                                                                                                        \
                if (ImGui::Button("Yes", ImVec2(120, 0))) {                                             \
                    response;                                                                           \
                    ImGui::CloseCurrentPopup();                                                         \
                }                                                                                       \
                ImGui::SetItemDefaultFocus();                                                           \
                ImGui::SameLine();                                                                      \
                if (ImGui::Button("No", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }                \
                ImGui::EndPopup();                                                                      \
            }                                                                                           \
        }                                                                                               \
        if ((j != (TextureGlobals::loaded.size() - 1) && ((j + 1) % 5))) {                              \
            ImGui::SameLine();                                                                          \
        }                                                                                               \
    }                                                                                                   \
    ImGui::EndChild();                                                                                  \
}                                                                                                       \

#define UI_TEXTURE_POSITION_MENU(object, loop, condition, check, rotArg, scaleArg, posArg) {            \
    ImGui::PushItemWidth(136);                                                                          \
                                                                                                        \
    float texRot = (object).getTextureRotation(check);                                                  \
    if (ImGui::InputFloat("Texture Rotation", &texRot, 5.0f, 10.0f, "%0.1f"))                           \
        loop {                                                                                          \
            condition {                                                                                 \
                (object).rotArg;                                                                        \
            }                                                                                           \
        }                                                                                               \
                                                                                                        \
    float texScale = (object).getTextureScale(check);                                                   \
    if (ImGui::InputFloat("Texture Scale", &texScale, 0.25f, 1.0f, "%0.3f"))                            \
        loop {                                                                                          \
             condition {                                                                                \
                (object).scaleArg;                                                       \
             }                                                                                          \
        }                                                                                               \
                                                                                                        \
    glm::vec2 texPosition = (object).getTexturePosition(check);                                         \
    if (ImGui::InputFloat2("Texture Position", &texPosition.x, "%0.3f"))                                \
        loop {                                                                                          \
             condition{                                                                                 \
                (object).posArg;                                                 \
             }                                                                                          \
        }                                                                                               \
                                                                                                        \
    ImGui::PopItemWidth();                                                                              \
}

#define BOX_TEXTURE_POSITION_MENU(object, loop, condition, check) UI_TEXTURE_POSITION_MENU(object, loop, condition, check,  \
                                  setTextureRotation(n, texRot),                                                           \
                                  setTextureScale(n, texScale),                                                             \
                                  setTexturePosition(n, texPosition))                                                       \

#define TILE_TEXTURE_POSITION_MENU(object, loop, condition, check) UI_TEXTURE_POSITION_MENU(object, loop, condition, check, \
                                  setTextureRotation(texRot),                                                              \
                                  setTextureScale(texScale),                                                                \
                                  setTexturePosition(texPosition))                                                          \


#define BOX_SELECTABLE_LIST_NO_SET(box, outVec) UI_SELECTABLE_LIST(box.getTileList(), outVec, openWindows[boolKey], , "Box", box.getName(), "IndTex", ImVec2(136,150))
#define BOX_SELECTABLE_LIST_SET(box, outVec, getter, setter) UI_SELECTABLE_LIST(box.getTileList(), outVec, getter, setter, "Box", box.getName(), "IndTex", ImVec2(136,150))


#endif //CALEBSRENDERER_BOXMACROS_H
