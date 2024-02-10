//
// Created by Caleb Rutledge on 1/12/24.
//



#include "Light.h"


Light::Light(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif) {
    ambient = amb;
    specular = spec;
    diffuse = dif;
}

LimitedLight::LimitedLight(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): Light(amb, spec, dif) {
    constant = con;
    linear = lin;
    quadratic = quad;
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): LimitedLight(amb, spec, dif, con, lin, quad) {
    position = pos;
}

DirectionLight::DirectionLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): Light(amb, spec, dif) {
    direction = dir;
}

void PointLight::setPosition(glm::vec3 pos) {
    position = pos;
}