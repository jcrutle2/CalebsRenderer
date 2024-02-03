//
// Created by Caleb Rutledge on 1/12/24.
//

#define AMBIENT_DEFAULT glm::vec3(0.3f, 0.3f, 0.3f)
#define SPECULAR_DEFAULT glm::vec3(0.2f, 0.2f, 0.2f)
#define DIFFUSE_DEFAULT glm::vec3(0.2f, 0.2f, 0.2f)
#define CONSTANT_DEFAULT 1.0f
#define LINEAR_DEFAULT 0.18f
#define QUADRATIC_DEFAULT 0.09f

#include "../Headers/Light.h"


Light::Light(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif) {
    ambient = amb;
    specular = spec;
    diffuse = dif;
}

Light::Light() {
    ambient = AMBIENT_DEFAULT;
    specular = SPECULAR_DEFAULT;
    diffuse = DIFFUSE_DEFAULT;
}

LimitedLight::LimitedLight(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): Light(amb, spec, dif) {
    constant = con;
    linear = lin;
    quadratic = quad;
}

LimitedLight::LimitedLight(glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): Light(amb, spec, dif) {
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

LimitedLight::LimitedLight(): Light() {
    constant = CONSTANT_DEFAULT;
    linear = LINEAR_DEFAULT;
    quadratic = QUADRATIC_DEFAULT;
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): LimitedLight(amb, spec, dif, con, lin, quad) {
    position = pos;
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): LimitedLight(amb, spec, dif) {
    position = pos;
}


PointLight::PointLight(glm::vec3 pos): LimitedLight() {
    position = pos;
}

PointLight::PointLight(): LimitedLight(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), 0, 0, 0){
    position = glm::vec3(0,0,0);
}

DirectionLight::DirectionLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): Light(amb, spec, dif) {
    direction = dir;
}

DirectionLight::DirectionLight(glm::vec3 dir): Light() {
    direction = dir;
}

DirectionLight::DirectionLight(): Light(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0)) {
    direction = glm::vec3(0,0,0);
}

void PointLight::setPosition(glm::vec3 pos) {
    position = pos;
}