//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

bool my_tool_active = true;

namespace UI {
    std::unordered_map<int, bool> openModels;
    std::unordered_map<int, bool> openLights;
    std::unordered_map<int, bool> openBox;
    bool openLoadModel = false;
    bool openDirLight = false;
    bool openLoadScene = false;
    bool openChangeSkybox = false;
    std::string filePath = fs::current_path();
    std::string modelPath = filePath + "/Assets/Models";
    std::string scenesPath = filePath + "/Assets/Scenes";
    std::string skyboxPath = filePath + "/Assets/Skyboxes";
    char nameBuf[32] = "";
    char sceneBuf[64] = "";
    char lightBuf[32] = "";
    const char boxSides[6][2] = {"F", "B", "L", "R", "T", "B"};
}