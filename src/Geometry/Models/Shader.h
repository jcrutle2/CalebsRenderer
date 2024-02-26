#ifndef SHADER_H
#define SHADER_H

#pragma once

#include "glew.h" // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm.hpp"
#include "../../Environment/Light/Light.h"
#include "../../Rendering/Camera.h"
#include "Model.h"
#include "../../Entities/Entity.h"

class Shader
{
    public:
    // the program ID
        unsigned int ID;
    // constructor reads and builds the shader
        Shader();
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
    // use/activate the shader
        void use();
    // utility uniform functions
        void setBool(const std::string &name, const bool &value) const;
        void setInt(const std::string &name, const int &value) const;
        void setFloat(const std::string &name, const float &value) const;
        void setVec3(const std::string &name, const float &x, const float &y, const float &z) const;
        void setVec3(const std::string &name, const glm::vec3 &vec) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;

    // light functions
        void setDirectionLight(const DirectionLight &d) const;
        void setPointLight(const PointLight &p, const int &num, const glm::vec3 &offset = (glm::vec3(0.0f))) const;
        void setPointLights(const std::vector<PointLight> &vec, const std::vector<Entity> &m) const;

    // camera functions
        void setMats(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const;
        void setModel(const glm::mat4 &model) const;
        void setCamera(const Camera &cam) const;
};

#endif
