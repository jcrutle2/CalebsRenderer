//
// Created by Caleb Rutledge on 1/12/24.
//

#ifndef OPENGL_TESTS_LIGHT_H
#define OPENGL_TESTS_LIGHT_H

#include <glm.hpp>


class Light {
    public:
        Light(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif);
        Light();
        glm::vec3 ambient{};
        glm::vec3 specular{};
        glm::vec3 diffuse{};
    private:
};

class LimitedLight : public Light {
    public:
        LimitedLight(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad);
        LimitedLight(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif);
        LimitedLight();
        float constant;
        float linear;
        float quadratic;
    private:
};

class PointLight : public LimitedLight {
    public:
        PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad);
        PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif);
        PointLight(glm::vec3 pos);
        PointLight();
        glm::vec3 position{};
        void setPosition(glm::vec3 pos);
};

class DirectionLight : public Light {
    public:
        DirectionLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif);
        DirectionLight(glm::vec3 dir);
        DirectionLight();
        glm::vec3 direction{};
};


#endif //OPENGL_TESTS_LIGHT_H
