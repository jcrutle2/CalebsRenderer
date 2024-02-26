//
// Created by Caleb Rutledge on 2/10/24.
//

#ifndef CALEBSRENDERER_SKYBOX_H
#define CALEBSRENDERER_SKYBOX_H

#include "../../Geometry/Models/Shader.h"
#include <vector>
#include "glm.hpp"

class Skybox {
public:
    Skybox();
    Skybox(Skybox &s);
    Skybox& operator= (const Skybox &s);
    void loadSkybox(const std::string &dir);
    void draw(glm::mat4 view, glm::mat4 projection);
    void deactivate();
    bool active;

    template<class Archive>
    void save(Archive &ar) const;
    template<class Archive>
    void load(Archive &ar);
    char directory[128];

private:
    unsigned int textureID;
    Shader shader;
    unsigned int VAO, VBO, EBO;
    bool initialized;
};


#endif //CALEBSRENDERER_SKYBOX_H
