//
// Created by Caleb Rutledge on 2/18/24.
//

#include "Texture.h"

std::string TextureGlobals::fileExtension (const std::string &file) {
    for (int i = file.length() - 1; i >= 0; i--) {
        if (file[i] == '.') {
            return file.substr(i + 1, file.length() - (i + 1));
        }
    }
    return "";
}

std::string TextureGlobals::shorten(const std::string &s) {
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] == '/') {
            return s.substr(i, s.length() - i);
        }
    }
    return "";
}

void TextureGlobals::loadAllTextures() {
    std::string texturePath = static_cast<std::string>(std::filesystem::current_path()) + "/Assets/Textures";

    Texture t;
    for (const auto& entry : std::filesystem::directory_iterator(texturePath)) {
        std::string entryPath = entry.path();
        std::string shortPath = shorten(entryPath);

        if (std::filesystem::is_directory(entryPath)) {
            std::string pngPath = "";
            std::string jpgPath = "";
            for (const auto &entryTex : std::filesystem::directory_iterator(entryPath)) {
                if (shorten(entryTex.path()) == "/main.png") {
                    pngPath = ("Assets/Textures" + shortPath + "/main.png");
                }
                if (shorten(entryTex.path()) == "/main.jpg") {
                    jpgPath = ("Assets/Textures" + shortPath + "/main.jpg");
                }
            }
            if (!pngPath.empty() && !jpgPath.empty()) {
                throw std::invalid_argument("Error: found JPG and PNG path to texture");
            }
            else if (!pngPath.empty()) {
                newTexture(t, pngPath.c_str(), "png");
            }
            else if (!jpgPath.empty()) {
                newTexture(t, jpgPath.c_str(), "jpg");
            }
        }
        else
            newTexture(t, ("Assets/Textures" + shortPath).c_str(), fileExtension(shortPath).c_str());
    }
}