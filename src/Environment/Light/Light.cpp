//
// Created by Caleb Rutledge on 1/12/24.
//



#include "Light.h"


Light::Light(const std::string &n, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif) {
    name = n;
    ambient = amb;
    specular = spec;
    diffuse = dif;
}

LimitedLight::LimitedLight(const std::string &n, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): Light(n, amb, spec, dif) {
    constant = con;
    linear = lin;
    quadratic = quad;
}

PointLight::PointLight(const std::string &n, glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): LimitedLight(n, amb, spec, dif, con, lin, quad) {
    position = pos;
}

PointLight& PointLight::operator=(const PointLight &p) {
    return *this;
}

PointLight::PointLight(const PointLight &P) : LimitedLight(P.name, P.ambient, P.specular, P.diffuse, P.constant, P.linear, P.quadratic) {
    position = P.position;
}

DirectionLight::DirectionLight(const std::string &n, glm::vec3 dir, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): Light(n, amb, spec, dif) {
    direction = dir;
}

DirectionLight& DirectionLight::operator=(const DirectionLight &d) {
    return *this;
}

DirectionLight::DirectionLight(const DirectionLight &D) : Light(D.name, D.ambient, D.specular, D.diffuse) {
    direction = D.direction;
}

void PointLight::setPosition(glm::vec3 pos) {
    position = pos;
}