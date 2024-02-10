//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

bool my_tool_active = true;

namespace UI {
    std::unordered_map<int, bool> openModels;
    std::unordered_map<int, bool> openLights;
    bool addModelWindow = false;
    bool openDirLight = false;
    bool openLoadModel = false;
    bool openChangeSkybox = false;
    std::string filePath = fs::current_path();
    std::string path = filePath;
    std::string scenesPath = filePath + "/Scenes";
    std::string skyboxPath = filePath + "/Textures";
    char nameBuf[32] = "";
    char sceneBuf[64] = "";

}