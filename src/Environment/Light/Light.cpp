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

std::string Light::getName() const { return name; }
glm::vec3 Light::getAmbient() const { return ambient; }
glm::vec3 Light::getSpecular() const{ return specular; }
glm::vec3 Light::getDiffuse() const { return diffuse; }

void Light::setName(const std::string &n) { name = n; }
void Light::setAmbient(const glm::vec3 &v) { ambient = v; }
void Light::setSpecular(const glm::vec3 &v) { specular = v; }
void Light::setDiffuse(const glm::vec3 &v) { diffuse = v; }

LimitedLight::LimitedLight(const std::string &n, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): Light(n, amb, spec, dif) {
    constant = con;
    linear = lin;
    quadratic = quad;
}

float LimitedLight::getConstant() const { return constant; }
float LimitedLight::getLinear() const { return linear; }
float LimitedLight::getQuadratic() const { return quadratic; }

void LimitedLight::setConstant(const float &f) { constant = f; }
void LimitedLight::setLinear(const float &f) { linear = f; }
void LimitedLight::setQuadratic(const float &f) { quadratic = f; }

PointLight::PointLight(const std::string &n, glm::vec3 pos, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif, float con, float lin, float quad): LimitedLight(n, amb, spec, dif, con, lin, quad) {
    position = pos;
}

PointLight& PointLight::operator=(const PointLight &p) {
    position = p.position;
    ambient = p.ambient;
    diffuse = p.diffuse;
    specular = p.specular;
    constant = p.constant;
    linear = p.linear;
    quadratic = p.quadratic;
    return *this;
}

PointLight::PointLight(const PointLight &P) : LimitedLight(P.name, P.ambient, P.specular, P.diffuse, P.constant, P.linear, P.quadratic) {
    position = P.position;
}

glm::vec3 PointLight::getPosition() const { return position; }
void PointLight::setPosition(glm::vec3 pos) { position = pos; }

DirectionLight::DirectionLight(const std::string &n, glm::vec3 dir, glm::vec3 amb, glm::vec3 spec, glm::vec3 dif): Light(n, amb, spec, dif) {
    direction = dir;
}

DirectionLight& DirectionLight::operator=(const DirectionLight &d) {
    direction = d.direction;
    ambient = d.ambient;
    diffuse = d.diffuse;
    specular = d.specular;
    return *this;
}

DirectionLight::DirectionLight(const DirectionLight &D) : Light(D.name, D.ambient, D.specular, D.diffuse) {
    direction = D.direction;
}

glm::vec3 DirectionLight::getDirection() const { return direction; }
void DirectionLight::setDirection(glm::vec3 dir) { direction = dir; }

