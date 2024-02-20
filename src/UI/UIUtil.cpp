//
// Created by Caleb Rutledge on 2/9/24.
//

#include "UI.h"

void UI::back(std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '/') {
            s = s.substr(0, i);
            return;
        }
    }
}

std::string UI::shorten(const std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '/') {
            return s.substr(i, s.length() - i);
        }
    }
    return "";
}

std::string UI::fileExtension(const std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '.') {
            return s.substr(i, s.length() - i);
        }
    }
    return "";
}

std::string UI::getKey(const std::string &type, const std::string &name, const std::string &sub, const std::string &sub2) {
    return type + "_" + name + "_" + sub + "_" + sub2;
}

std::string UI::getKeySubSubType(const std::string &key) {
    int typeEnd = -1;
    int nameEnd = -1;
    int subEnd = -1;

    int iter = 0;
    for (const auto &ch : key) {
        if (ch == '_') {
            if (typeEnd == -1) {
                typeEnd = iter;
            }
            else if (nameEnd == -1) {
                nameEnd = iter;
            }
            else if (subEnd == -1) {
                subEnd = iter;
            }
            else {
                throw std::invalid_argument("ERROR: Invalid Key Type");
            }
        }
        iter++;
    }

    return key.substr(subEnd + 1);
}

std::string UI::getKeySubType(const std::string &key) {
    int typeEnd = -1;
    int nameEnd = -1;
    int subEnd = -1;

    int iter = 0;
    for (const auto &ch : key) {
        if (ch == '_') {
            if (typeEnd == -1) {
                typeEnd = iter;
            }
            else if (nameEnd == -1) {
                nameEnd = iter;
            }
            else if (subEnd == -1) {
                subEnd = iter;
            }
            else {
                throw std::invalid_argument("ERROR: Invalid Key Type");
            }
        }
        iter++;
    }

    return key.substr((nameEnd + 1), (subEnd - nameEnd) - 1);
}

std::string UI::getKeyName(const std::string &key) {
    int typeEnd = -1;
    int nameEnd = -1;
    int subEnd = -1;

    int iter = 0;
    for (const auto &ch : key) {
        if (ch == '_') {
            if (typeEnd == -1) {
                typeEnd = iter;
            }
            else if (nameEnd == -1) {
                nameEnd = iter;
            }
            else if (subEnd == -1) {
                subEnd = iter;
            }
            else {
                throw std::invalid_argument("ERROR: Invalid Key Type");
            }
        }
        iter++;
    }

    std::string retVal = key.substr((typeEnd + 1), (nameEnd - typeEnd) - 1);
    return retVal;
}

std::string UI::getKeyType(const std::string &key) {
    int typeEnd = -1;
    int nameEnd = -1;
    int subEnd = -1;

    int iter = 0;
    for (const auto &ch : key) {
        if (ch == '_') {
            if (typeEnd == -1) {
                typeEnd = iter;
            }
            else if (nameEnd == -1) {
                nameEnd = iter;
            }
            else if (subEnd == -1) {
                subEnd = iter;
            }
            else {
                throw std::invalid_argument("ERROR: Invalid Key Type");
            }
        }
        iter++;
    }

    return key.substr(0, typeEnd);
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