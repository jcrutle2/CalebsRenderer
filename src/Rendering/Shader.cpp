//
// Created by Caleb Rutledge on 1/3/24.
//

#include "../Headers/Shader.h"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

Shader::Shader() {
    ID = 0;
}
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
// 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

// 2. compile shaders

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                  infoLog << std::endl;
    };

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    // ensure shader was successful
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
                  infoLog << std::endl;
    };

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
// print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
                  infoLog << std::endl;
    }
// delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
Shader::~Shader() = default;

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, GLint value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 &vec) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setMat4(const std::string &name, glm::mat4 &mat) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMats(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const {
    glm::mat4 invModel = glm::inverse(model);
    setMat4("model", model);
    setMat4("view", view);
    setMat4("projection", projection);
    setMat4("invModel", invModel);
}

void Shader::setModel(glm::mat4 model) const {
    glm::mat4 invModel = glm::inverse(model);
    setMat4("model", model);
    setMat4("invModel", invModel);
}

void Shader::setDirectionLight(DirectionLight &d) const {
    setVec3("dirLight.direction", d.direction);
    setVec3("dirLight.ambient",  d.ambient);
    setVec3("dirLight.diffuse",  d.diffuse);
    setVec3("dirLight.specular", d.specular);
}

void Shader::setPointLight(PointLight &p, int num) const {
    std::string path = "pointLights[" + std::to_string(num) + "].";
    setVec3(path + "position", p.position);
    setVec3(path + "ambient",  p.ambient);
    setVec3(path + "diffuse",  p.diffuse);
    setVec3(path + "specular", p.specular);
    setFloat(path + "constant", p.constant);
    setFloat(path + "linear",  p.linear);
    setFloat(path + "quadratic",  p.quadratic);
}

void Shader::setPointLights(std::vector<PointLight> &vec) const {
    for (int i = 0; i < vec.size(); i++) {
        setPointLight(vec[i], i);
    }
    setInt("size", static_cast<int>(vec.size()));
}

void Shader::setCamera(Camera cam) const {
    setVec3("camPos", cam._cameraPos);
}