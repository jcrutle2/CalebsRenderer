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

        newTexture(t, ("Assets/Textures" + shortPath).c_str(), fileExtension(shortPath).c_str());
    }
}