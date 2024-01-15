#ifndef SHADER_H
#define SHADER_H

#include <glew.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include "Light.h"
#include "Camera.h"

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
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec3(const std::string &name, glm::vec3 &vec) const;
        void setMat4(const std::string &name, glm::mat4 &mat) const;

    // light functions
        void setDirectionLight(DirectionLight &d ) const;
        void setPointLight(PointLight &p, int num) const;
        void setPointLights(std::vector<PointLight> &vec) const;
    // camera functions
        void setMats(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
        void setCamera(Camera cam) const;
};

#endif
