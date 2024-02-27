//
// Created by Caleb Rutledge on 2/27/24.
//

#ifndef CALEBSRENDERER_MODELMACROS_H
#define CALEBSRENDERER_MODELMACROS_H

#define MODEL_LIGHT_SELECTABLE_LIST(entity)                             \
    UI_SELECTABLE_LIST(entity.getLightsList(),                          \
                        boolKeys,                                       \
                        openWindows[boolKey],                           \
                        ,                                               \
                        "Entity",                                       \
                        entity.getName(),                               \
                        "Lights",                                       \
                        ImVec2(136,150),                                \
                        if (ImGui::Button("Add Light")) {               \
                            std::string name = "Light" + std::to_string(entity.getLightsList().size() + 1); \
                            entity.pushBackLight(name);                 \
    });

#define MODEL_LIGHT_WINDOW_MULTIPLE(obj, key) {                                                 \
    if (!key.empty()) {                                                                         \
    int check = 0;                                                                              \
    for (int j = 0; j < key.size(); j++) {                                                      \
        if (openWindows[key[j]]) {                                                              \
            check = j;                                                                          \
            break;                                                                              \
        }                                                                                       \
    }                                                                                           \
    POINT_LIGHT_WINDOW_MULTIPLE(obj.getLightsList(), check,                                     \
                                for (int n = 0; n < obj.getLightsList().size(); n++),           \
                                if (openWindows[boolKeys[n]]));                                 \
    }                                                                                           \
}

#endif //CALEBSRENDERER_MODELMACROS_H