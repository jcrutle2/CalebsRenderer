//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

void UI::mainWindow(Scene &s, Camera &c, const std::string &frameRate) {
    ImGui::Text("%s", ("Frame Rate: " + frameRate).c_str());
    ImGui::InputFloat3("Camera", &c.cameraPos.x);

    ImGui::Text("\nModel List: ");
    int modelCount = 0;
    for (auto const &m : s.models) {
        if (ImGui::Button(m.name.c_str())) {
            openModels[modelCount] = true;
        }
        modelCount++;
    }
    if (ImGui::Button("Add Model")) {
        openLoadModel = true;
    }

    ImGui::Text("\nLight List");
    if (ImGui::Button("Direction Light")) {
        openDirLight = true;
    }
    for (int i = 0; i < s.pointLights.size(); i++) {
        std::string n = s.pointLights[i].name;
        if (ImGui::Button(n.c_str())) {
            openLights[i] = true;
        }
    }
    if (ImGui::Button("Add Light")) {
        std::string name = "Light" + std::to_string(s.pointLights.size() + 1);
        s.pointLights.emplace_back(name);
    }

    ImGui::Text("\nSkybox");
    if (ImGui::Button("Change Skybox")) {
        openChangeSkybox = true;
    }

    ImGui::Text("\nScene Info");
    ImGui::InputText("Name", sceneBuf, 64);
    if (ImGui::Button("Save Scene")) {
        std::string savePath = "Assets/Scenes/";
        savePath += (strcmp(sceneBuf, "")) ? sceneBuf : "scene";
        savePath += ".bin";
        SceneLoader::storeScene(s, savePath);
    }
    if (ImGui::Button("Load Scene")) {
        openLoadScene = true;
    }
}

void UI::modelWindow(std::vector<Model> &m, int num) {
    ImGui::Begin(m[num].name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputText("Name", nameBuf, 32);
    if (ImGui::Button("Save Name")) {
        m[num].name = nameBuf;
    }

    ImGui::InputFloat3("Position", &m[num].position.x);
    ImGui::InputFloat("Rotation", &m[num].rotation);
    ImGui::InputFloat3("Axis", &m[num].rotationAxis.x);
    ImGui::InputFloat3("Scale", &m[num].scale.x);

    ImGui::Text("\nLight List");
    for (int i = 0; i < m[num].lights.size(); i++) {
        std::string n = m[num].lights[i].name;
        if (ImGui::Button(n.c_str())) {
            openLights[i] = true;
        }
    }
    if (ImGui::Button("Add Light")) {
        std::string name = "Light" + std::to_string(m[num].lights.size() + 1);
        m[num].lights.emplace_back(name);
    }

    if(ImGui::MenuItem("Delete")) {
        for (auto x : openModels) {
            x.second = false;
        }
        m.erase(m.begin() + num);
    }
    if(ImGui::MenuItem("Close")) {
            openModels[num] = false;
    }

    ImGui::End();
}

void UI::directionLightWindow(DirectionLight &l) {
    ImGui::Begin("Direction Light", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputFloat3("Direction", &l.direction.x);
    ImGui::InputFloat3("Ambient", &l.ambient.x);
    ImGui::InputFloat3("Specular", &l.specular.x);
    ImGui::InputFloat3("Diffuse", &l.diffuse.x);
    if(ImGui::MenuItem("Close")) {
        openDirLight = false;
    }

    ImGui::End();
}

void UI::lightWindow(std::vector<PointLight> &lights, int num) {
    std::string name = lights[num].name;
    PointLight &l = lights[num];
    ImGui::Begin(name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputText("Name", lightBuf, 32);
    if (ImGui::Button("Save Name")) {
        if (strcmp(lightBuf, ""))
            lights[num].name = lightBuf;
    }

    ImGui::InputFloat3("Position", &l.position.x);
    ImGui::InputFloat3("Ambient", &l.ambient.x);
    ImGui::InputFloat3("Specular", &l.specular.x);
    ImGui::InputFloat3("Diffuse", &l.diffuse.x);
    ImGui::InputFloat("Constant Falloff", &l.constant);
    ImGui::InputFloat("Linear Falloff", &l.linear);
    ImGui::InputFloat("Quadratic Falloff", &l.quadratic);


    if(ImGui::MenuItem("Delete")) {
        for (auto x : openLights) {
            x.second = false;
        }
        lights.erase(lights.begin() + num);
    }
    if(ImGui::MenuItem("Close")) {
        openLights[num] = false;
    }

    ImGui::End();
}

void UI::newModelWindow(std::vector<Model> &m) {
    ImGui::Begin("Add Model", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", modelPath.c_str());

    for (const auto& entry : fs::directory_iterator(modelPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            std::string f = fileExtension(shortPath);
            if (f != ".jpg" && f != ".png") {
                if (ImGui::Button(shortPath.c_str())) {
                    if (fs::is_directory(entry))
                        modelPath = entry.path();
                    else {
                        m.emplace_back(Model(shortPath.substr(1, shortPath.length() - 1), static_cast<std::string>(entry.path())));
                        openLoadModel = false;
                    }
                }
            }
        }
    }

    if(ImGui::MenuItem("Back")) {
        UI::back(modelPath);
    }

    if(ImGui::MenuItem("Close")) {
        openLoadModel = false;
    }

    ImGui::End();
}

void UI::loadSceneWindow(Scene &s) {
    ImGui::Begin("Load Scene", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", scenesPath.c_str());

    for (const auto& entry : fs::directory_iterator(scenesPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            if (ImGui::Button(shortPath.c_str())) {
                std::string getScenePath = "Assets/Scenes";
                getScenePath += shortPath;
                s = SceneLoader::getSceneFromDisk(getScenePath);
                openLoadScene = false;
            }
        }
    }

    if(ImGui::MenuItem("Close")) {
        openLoadScene = false;
    }

    ImGui::End();
}

void UI::changeSkyboxWindow(Skybox &s) {
    ImGui::Begin("Change Skybox", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text("%s", scenesPath.c_str());

    for (const auto& entry : fs::directory_iterator(skyboxPath)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            if (ImGui::Button(shortPath.substr(1, shortPath.length() - 1).c_str())) {
                std::string skyboxDirectory = "Assets/Skyboxes" + shortPath;
                s.loadSkybox(skyboxDirectory);
                openChangeSkybox = false;
            }
        }
    }

    if(ImGui::MenuItem("Close")) {
        openChangeSkybox = false;
    }

    ImGui::End();
}