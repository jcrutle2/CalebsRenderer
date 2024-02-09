//
// Created by Caleb Rutledge on 2/3/24.
//

#include "UI.h"
#include <algorithm>

bool my_tool_active = true;

namespace UI {
    std::unordered_map<int, bool> openModels;
    bool addModelWindow;
    bool openDirLight;
    std::unordered_map<int, bool> openLights;
    std::string filePath = fs::current_path();
    std::string path = filePath;
    char nameBuf[32] = "";
    void back(std::string &s) {
        for (int i = s.length() - 1; i > 0; i--) {
            if (s[i] == '/') {
                s = s.substr(0, i);
                return;
            }
        }
    }
    std::string shorten(const std::string &s) {
        for (int i = s.length() - 1; i > 0; i--) {
            if (s[i] == '/') {
                return s.substr(i, s.length() - i);
            }
        }
    }
}

void UI::Initalize(SDL_Window * window, void * sdl_gl_context) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    if (io.BackendPlatformUserData == nullptr) {
        ImGui_ImplSDL2_InitForOpenGL(window, sdl_gl_context);
        ImGui_ImplOpenGL3_Init();
    }
}

void UI::mainWindow(std::vector<Model> &models, DirectionLight dirLight, std::vector<PointLight> &pointLights, std::string frameRate) {
    ImGui::Text(("Frame Rate: " + frameRate).c_str());

    ImGui::Text("Model List: ");
    int modelCount = 0;
    for (auto const &m : models) {
        if (ImGui::Button(m.name)) {
            openModels[modelCount] = true;
        }
        modelCount++;
    }
    if (ImGui::Button("Add Model")) {
        addModelWindow = true;
    }


    ImGui::Text("\nLight List");
    if (ImGui::Button("Direction Light")) {
        openDirLight = true;
    }
    for (int i = 0; i < pointLights.size(); i++) {
        std::string n = "Light " + std::to_string(i);
        if (ImGui::Button(n.c_str())) {
            openLights[i] = true;
        }
    }
    if (ImGui::Button("Add Light")) {
        pointLights.emplace_back(PointLight());
    }
}

void UI::modelWindow(Model &m, int num) {
    ImGui::Begin(m.name, &my_tool_active, ImGuiWindowFlags_MenuBar);


    ImGui::InputText("Name", nameBuf, 32);
    if (ImGui::Button("Save Name")) {
        strcpy(m.name, nameBuf);
    }

    ImGui::InputFloat3("Position", &m.position.x);
    ImGui::InputFloat("Rotation", &m.rotation);
    ImGui::InputFloat3("Axis", &m.rotationAxis.x);
    ImGui::InputFloat3("Scale", &m.scale.x);

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
    std::string name = "Light " + std::to_string(num);
    PointLight &l = lights[num];
    ImGui::Begin(name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::InputFloat3("Position", &l.position.x);
    ImGui::InputFloat3("Ambient", &l.ambient.x);
    ImGui::InputFloat3("Specular", &l.specular.x);
    ImGui::InputFloat3("Diffuse", &l.diffuse.x);
    ImGui::InputFloat("Constant Falloff", &l.constant);
    ImGui::InputFloat("Linear Falloff", &l.linear);
    ImGui::InputFloat("Quadratic Falloff", &l.quadratic);

    if(ImGui::MenuItem("Close")) {
        openLights[num] = false;
    }

    ImGui::End();
}

void UI::newModelWindow(std::vector<Model> &m) {
    ImGui::Begin("Add Model", &my_tool_active, ImGuiWindowFlags_MenuBar);

    ImGui::Text(path.c_str());

    for (const auto& entry : fs::directory_iterator(path)) {
        std::string entryPath = entry.path();
        std::string shortPath = UI::shorten(entryPath);

        if (shortPath[1] != '.') {
            if (ImGui::Button(shortPath.c_str())) {
                if (fs::is_directory(entry))
                    path = entry.path();
                else {
                    m.emplace_back(Model("New Model", static_cast<std::string>(entry.path())));
                    addModelWindow = false;
                }
            }
        }
    }

    if(ImGui::MenuItem("Back")) {
        UI::back(path);
    }

    if(ImGui::MenuItem("Close")) {
        addModelWindow = false;
    }

    ImGui::End();
}

void UI::renderWindows(std::vector<Model> &models, DirectionLight &dirLight, std::vector<PointLight> &pointLights, std::string frameRate) {
    mainWindow(models, dirLight, pointLights, frameRate);

    int modelCount = 0;
    for (auto &model : models) {
        if (openModels[modelCount]) modelWindow(model, modelCount);
        modelCount++;
    }

    if (openDirLight) directionLightWindow(dirLight);

    int lightCount = 0;
    for (auto &light : pointLights) {
        if (openLights[lightCount]) lightWindow(pointLights, lightCount);
        lightCount++;
    }

    if (addModelWindow) newModelWindow(models);
    else path = filePath;
}

void UI::FrameStart() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UI::FrameEnd() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}