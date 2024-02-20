//
// Created by Caleb Rutledge on 2/18/24.
//

#include "Texture.h"
#include <glew.h>
#include <iostream>

namespace TextureGlobals {
    std::vector<Texture> loaded;
}

void newTexture(Texture &t, const char* path, const char* type) {
    for (auto tex : TextureGlobals::loaded) {
        if (std::strcmp(tex.path.data, path) == 0) {
            t = tex;
            return;
        }
    }

    glGenTextures(1, &t.id);
    glBindTexture(GL_TEXTURE_2D, t.id);
// set the Texture wrapping/filtering options (on currently bound Texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the Texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height,
                                    &nrChannels, 0);
    if (data)
    {
        if (!strcmp(type, "jpg"))
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load Texture" << std::endl;
    }
    stbi_image_free(data);

    t.type = type;
    t.path = path;
    TextureGlobals::loaded.push_back(t);
}

void useTexture(const Texture &t) {
    glBindTexture(GL_TEXTURE_2D, t.id);
}

