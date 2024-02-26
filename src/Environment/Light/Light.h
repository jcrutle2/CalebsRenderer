//
// Created by Caleb Rutledge on 1/12/24.
//

#ifndef OPENGL_TESTS_LIGHT_H
#define OPENGL_TESTS_LIGHT_H

#define DIRECTION_DEFAULT glm::vec3(0,-1.0f,0)
#define POSITION_DEFAULT glm::vec3(0,0,0)
#define AMBIENT_DEFAULT glm::vec3(0.4f, 0.4f, 0.4f)
#define SPECULAR_DEFAULT glm::vec3(0.5f, 0.5f, 0.5f)
#define DIFFUSE_DEFAULT glm::vec3(0.4f, 0.4f, 0.4f)
#define CONSTANT_DEFAULT 1.0f
#define LINEAR_DEFAULT 0.18f
#define QUADRATIC_DEFAULT 0.09f
#define POINTLIGHT_NAME_DEFAULT "Light"
#define DIRLIGHT_NAME_DEFAULT "Direction Light"

#include "glm.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/access.hpp"


class Light {
    public:
        explicit Light(const std::string &n, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT);
        std::string getName() const;
        glm::vec3 getAmbient() const;
        glm::vec3 getSpecular() const;
        glm::vec3 getDiffuse() const;

        void setName(const std::string &n);
        void setAmbient(const glm::vec3 &v);
        void setSpecular(const glm::vec3 &v);
        void setDiffuse(const glm::vec3 &v);

    protected:
        std::string name;
        glm::vec3 ambient{};
        glm::vec3 specular{};
        glm::vec3 diffuse{};
};

class LimitedLight : public Light {
    public:
        explicit LimitedLight(const std::string &n, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT, float con = CONSTANT_DEFAULT, float lin = LINEAR_DEFAULT, float quad = QUADRATIC_DEFAULT);

        float getConstant() const;
        float getLinear() const;
        float getQuadratic() const;

        void setConstant(const float &f);
        void setLinear(const float &f);
        void setQuadratic(const float &f);

    protected:
        float constant;
        float linear;
        float quadratic;
};

class PointLight : public LimitedLight {
    public:
        explicit PointLight(const std::string &n = POINTLIGHT_NAME_DEFAULT, glm::vec3 pos = POSITION_DEFAULT, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT, float con = CONSTANT_DEFAULT, float lin = LINEAR_DEFAULT, float quad = QUADRATIC_DEFAULT);
        PointLight& operator= (const PointLight &p);
        PointLight(const PointLight &P);

        glm::vec3 getPosition() const;
        void setPosition(glm::vec3 pos);

    protected:
        glm::vec3 position;

    private:
        friend class cereal::access;
        friend class cereal::BinaryInputArchive;
        template<class Archive>
        void serialize(Archive &ar);
};

class DirectionLight : public Light {
    public:
        explicit DirectionLight(const std::string &n = DIRLIGHT_NAME_DEFAULT, glm::vec3 dir = DIRECTION_DEFAULT, glm::vec3 amb = AMBIENT_DEFAULT, glm::vec3 spec = SPECULAR_DEFAULT, glm::vec3 dif = DIFFUSE_DEFAULT);
        DirectionLight& operator= (const DirectionLight &d);
        DirectionLight(const DirectionLight &D);

    glm::vec3 getDirection() const;
        void setDirection(glm::vec3 dir);

    protected:
        glm::vec3 direction;

    private:
        friend class cereal::access;
        friend class cereal::BinaryInputArchive;
        template<class Archive>
        void serialize(Archive &ar);
};


#endif //OPENGL_TESTS_LIGHT_H
