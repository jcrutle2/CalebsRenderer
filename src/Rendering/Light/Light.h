//
// Created by Caleb Rutledge on 1/12/24.
//

#ifndef OPENGL_TESTS_LIGHT_H
#define OPENGL_TESTS_LIGHT_H

#define DIRECTION_DEFAULT glm::vec3(0,0,0)
#define POSITION_DEFAULT glm::vec3(0,0,0)
#define AMBIENT_DEFAULT glm::vec3(0.1f, 0.1f, 0.1f)
#define SPECULAR_DEFAULT glm::vec3(0.2f, 0.2f, 0.2f)
#define DIFFUSE_DEFAULT glm::vec3(0.4f, 0.4f, 0.4f)
#define CONSTANT_DEFAULT 1.0f
#define LINEAR_DEFAULT 0.18f
#define QUADRATIC_DEFAULT 0.09f

#include <glm.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>


class Light {
    public:
        explicit Light(glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT);
        glm::vec3 ambient{};
        glm::vec3 specular{};
        glm::vec3 diffuse{};
    private:
};

class LimitedLight : public Light {
    public:
        explicit LimitedLight(glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT, float con = CONSTANT_DEFAULT, float lin = LINEAR_DEFAULT, float quad = QUADRATIC_DEFAULT);
        float constant;
        float linear;
        float quadratic;
    private:
};

class PointLight : public LimitedLight {
    public:
        explicit PointLight(glm::vec3 pos = POSITION_DEFAULT, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT, float con = CONSTANT_DEFAULT, float lin = LINEAR_DEFAULT, float quad = QUADRATIC_DEFAULT);
        glm::vec3 position{};
        void setPosition(glm::vec3 pos);
        friend class cereal::access;
        friend class cereal::BinaryInputArchive;
        template<class Archive>
        void serialize(Archive &ar);
};

class DirectionLight : public Light {
    public:
        explicit DirectionLight(glm::vec3 dir = DIRECTION_DEFAULT, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT);
        glm::vec3 direction{};
        friend class cereal::access;
        friend class cereal::BinaryInputArchive;
        template<class Archive>
        void serialize(Archive &ar);
};


#endif //OPENGL_TESTS_LIGHT_H
