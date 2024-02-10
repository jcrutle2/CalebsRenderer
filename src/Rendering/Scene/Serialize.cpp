//
// Created by Caleb Rutledge on 2/9/24.
//

#include "Scene.h"
#include "ModelInfo.h"

template<class Archive>
void Model::serialize(Archive &ar) {
    ar (name);
    ar (src);
    ar (position.x);
    ar (position.y);
    ar (position.z);
    ar (rotation);
    ar (rotationAxis.x);
    ar (rotationAxis.y);
    ar (rotationAxis.z);
    ar (scale.x);
    ar (scale.y);
    ar (scale.z);
}

template<class Archive>
void PointLight::serialize(Archive &ar) {
    ar(position.x);
    ar(position.y);
    ar(position.z);
    ar(ambient.r);
    ar(ambient.g);
    ar(ambient.b);
    ar(specular.r);
    ar(specular.g);
    ar(specular.b);
    ar(diffuse.r);
    ar(diffuse.g);
    ar(diffuse.b);
    ar(constant);
    ar(linear);
    ar(quadratic);
}


template<class Archive>
void DirectionLight::serialize(Archive &ar) {
    ar(direction.x);
    ar(direction.y);
    ar(direction.z);
    ar(ambient.r);
    ar(ambient.g);
    ar(ambient.b);
    ar(specular.r);
    ar(specular.g);
    ar(specular.b);
    ar(diffuse.r);
    ar(diffuse.g);
    ar(diffuse.b);
}

template<class Archive>
void Skybox::serialize(Archive &ar) {
    ar(directory);
    ar(active);
}