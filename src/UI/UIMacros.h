//
// Created by Caleb Rutledge on 2/20/24.
//

#ifndef CALEBSRENDERER_UIMACROS_H
#define CALEBSRENDERER_UIMACROS_H

#endif //CALEBSRENDERER_UIMACROS_H

#define UI_LOCATION_MENU(item)    {                                                     \
    glm::vec3 position = (item).getPosition();                                          \
    glm::vec3 axis = (item).getRotationAxis();                                          \
    float rotation = (item).getRotation();                                              \
    glm::vec3 scale = (item).getScale();                                                \
    if (ImGui::InputFloat3("Position", &position.x)) {                                  \
        (item).setPosition(position);                                                   \
    }                                                                                   \
    if (ImGui::InputFloat("Rotation", &rotation)) {                                     \
        (item).setRotation(rotation);                                                   \
    }                                                                                   \
    if (ImGui::InputFloat3("Axis", &axis.x)) {                                          \
        (item).setRotationAxis(axis);                                                   \
    }                                                                                   \
    if (ImGui::InputFloat3("Scale", &scale.x)) {                                        \
        (item).setScale(scale);                                                         \
    }                                                                                   \
};

#define UI_SELECTABLE_LIST(inVec, outVec, getter, setter, type, subtype, subsubtype, s, adOp) {     \
if (ImGui::BeginListBox(" ", s))  {                                                                 \
    for (int counter = 0; counter < (inVec).size(); counter++){                                     \
        std::string boolKey = getKey((type), (subtype), (subsubtype), (inVec)[counter].getName());  \
                                                                                                    \
        openWindows[boolKey] = getter;                                                              \
                                                                                                    \
        bool flag = false;                                                                          \
        if (!openWindows[boolKey]) {                                                                \
            flag = true;                                                                            \
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(0.4f, 0.4f, 0.4f));                \
        }                                                                                           \
                                                                                                    \
        if (ImGui::Selectable(inVec[counter].getName().c_str())) {                                  \
            openWindows[boolKey] = !(openWindows[boolKey]);                                         \
            setter;                                                                                 \
        }                                                                                           \
                                                                                                    \
        if (flag) {                                                                                 \
            ImGui::PopStyleColor(1);                                                                \
        }                                                                                           \
                                                                                                    \
        (outVec).push_back(boolKey);                                                                \
    }                                                                                               \
    ImGui::EndListBox();                                                                            \
                                                                                                    \
    ImGui::SameLine();                                                                              \
                                                                                                    \
    ImGui::BeginChild("Select List Options", ImVec2(100,136));                                      \
        adOp;                                                                                       \
        if (ImGui::Button("Select All")) {                                                          \
            for (const auto & str : boolKeys) {                                                     \
                openWindows[str] = true;                                                            \
            }                                                                                       \
        }                                                                                           \
        if (ImGui::Button("Deselect All")) {                                                        \
            for (const auto & str : boolKeys) {                                                     \
                openWindows[str] = false;                                                           \
            }                                                                                       \
        }                                                                                           \
        if (ImGui::Button("Invert")) {                                                              \
            for (const auto & str : boolKeys) {                                                     \
                openWindows[str] = !openWindows[str];                                               \
            }                                                                                       \
        }                                                                                           \
    ImGui::EndChild();                                                                              \
}                                                                                                   \
};


#define UI_MAP_CLEANUP(kt, kn) {                                                                    \
    std::vector<std::string> cleanupKeys;                                                           \
    for (const auto &w : openWindows) {                                                             \
        if ((getKeyType(w.first) == kt) && (getKeyName(w.first) == kn)) {                           \
            cleanupKeys.push_back(w.first);                                                         \
        }                                                                                           \
    }                                                                                               \
    for (const auto &k : cleanupKeys) {                                                             \
        openWindows.erase(k);                                                                       \
    }                                                                                               \
                                                                                                    \
    cleanupKeys = {};                                                                               \
    for (const auto &w : charBuffers) {                                                             \
        if ((getKeyType(w.first) == kt) && (getKeyName(w.first) == kn)) {                           \
            cleanupKeys.push_back(w.first);                                                         \
        }                                                                                           \
    }                                                                                               \
    for (const auto &k : cleanupKeys) {                                                             \
        charBuffers.erase(k);                                                                       \
    }                                                                                               \
}

#define UI_SAFE_RENAME(obj, vec, type) { \
    if (*charBuffers[bufferKey] == '\0')                                                            \
        strcpy(charBuffers[bufferKey], obj.getName().c_str());                                      \
    ImGui::InputText(" ", charBuffers[bufferKey], 32);                                              \
    ImGui::SameLine();                                                                              \
    if (ImGui::Button("Save Name")) {                                                               \
        bool safeToRename = true;                                                                   \
        for (const auto &b : vec) {                                                                 \
            if (b.getName() == charBuffers[bufferKey]) {                                            \
            safeToRename = false;                                                                   \
            break;                                                                                  \
            }                                                                                       \
        }                                                                                           \
        if (safeToRename) {                                                                         \
            std::string oldName = obj.getName();                                                    \
            obj.setName(charBuffers[bufferKey]);                                                    \
            UI_MAP_CLEANUP(type, oldName);                                                          \
                                                                                                    \
            bufferKey = getKey(type, obj.getName());                                                \
            openWindows[bufferKey] = true;                                                          \
        }                                                                                           \
    }                                                                                               \
}