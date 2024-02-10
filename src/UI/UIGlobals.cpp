//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

bool my_tool_active = true;

namespace UI {
    std::unordered_map<int, bool> openModels;
    bool addModelWindow;
    bool openDirLight;
    std::unordered_map<int, bool> openLights;
    bool openLoadModel;
    std::string filePath = fs::current_path();
    std::string path = filePath;
    std::string scenesPath = filePath + "/Scenes";
    char nameBuf[32] = "";
    char sceneBuf[64] = "";

}