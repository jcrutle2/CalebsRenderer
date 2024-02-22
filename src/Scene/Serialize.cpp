//
// Created by Caleb Rutledge on 2/9/24.
//

#include "Scene.h"


template<class Archive>
void Model::save(Archive &ar) const{
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
    ar (lights);
}

template<class Archive>
void Model::load(Archive &ar){
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
    ar (lights);

    loadModel(src);
}

template<class Archive>
void Entity::save(Archive &ar) const{
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
    ar (lights);
    ar (hitbox);
}

template<class Archive>
void Entity::load(Archive &ar){
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
    ar (lights);
    ar (hitbox);

    loadModel(src);
}

template<class Archive>
void Hitbox::serialize(Archive &ar) {
    ar(verts[0].x);
    ar(verts[0].y);
    ar(verts[0].z);
    ar(verts[1].x);
    ar(verts[1].y);
    ar(verts[1].z);
    ar(verts[2].x);
    ar(verts[2].y);
    ar(verts[2].z);
    ar(verts[3].x);
    ar(verts[3].y);
    ar(verts[3].z);
    ar(verts[4].x);
    ar(verts[4].y);
    ar(verts[4].z);
    ar(verts[5].x);
    ar(verts[5].y);
    ar(verts[5].z);
    ar(verts[6].x);
    ar(verts[6].y);
    ar(verts[6].z);
    ar(verts[7].x);
    ar(verts[7].y);
    ar(verts[7].z);
}

template<class Archive>
void PointLight::serialize(Archive &ar) {
    ar(name);
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
    ar(name);
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

template<class Archive>
void Scene::serialize(Archive &ar) {
    ar(entities);
    ar(dirLight);
    ar(pointLights);
    ar(skybox);
    ar(boxes);
}

template<class Archive>
void Box::save(Archive &ar) const {
    ar(name);
    ar(position.x);
    ar(position.y);
    ar(position.z);
    ar(rotationAxis.x);
    ar(rotationAxis.y);
    ar(rotationAxis.z);
    ar(rotation);
    ar(scale.x);
    ar(scale.y);
    ar(scale.z);

    ar(boxVertices[0].x);
    ar(boxVertices[0].y);
    ar(boxVertices[0].z);
    ar(boxVertices[1].x);
    ar(boxVertices[1].y);
    ar(boxVertices[1].z);
    ar(boxVertices[2].x);
    ar(boxVertices[2].y);
    ar(boxVertices[2].z);
    ar(boxVertices[3].x);
    ar(boxVertices[3].y);
    ar(boxVertices[3].z);
    ar(boxVertices[4].x);
    ar(boxVertices[4].y);
    ar(boxVertices[4].z);
    ar(boxVertices[5].x);
    ar(boxVertices[5].y);
    ar(boxVertices[5].z);
    ar(boxVertices[6].x);
    ar(boxVertices[6].y);
    ar(boxVertices[6].z);
    ar(boxVertices[7].x);
    ar(boxVertices[7].y);
    ar(boxVertices[7].z);

    ar(tiles);
}

template<class Archive>
void Box::load(Archive &ar) {
    ar(name);
    ar(position.x);
    ar(position.y);
    ar(position.z);
    ar(rotationAxis.x);
    ar(rotationAxis.y);
    ar(rotationAxis.z);
    ar(rotation);
    ar(scale.x);
    ar(scale.y);
    ar(scale.z);

    ar(boxVertices[0].x);
    ar(boxVertices[0].y);
    ar(boxVertices[0].z);
    ar(boxVertices[1].x);
    ar(boxVertices[1].y);
    ar(boxVertices[1].z);
    ar(boxVertices[2].x);
    ar(boxVertices[2].y);
    ar(boxVertices[2].z);
    ar(boxVertices[3].x);
    ar(boxVertices[3].y);
    ar(boxVertices[3].z);
    ar(boxVertices[4].x);
    ar(boxVertices[4].y);
    ar(boxVertices[4].z);
    ar(boxVertices[5].x);
    ar(boxVertices[5].y);
    ar(boxVertices[5].z);
    ar(boxVertices[6].x);
    ar(boxVertices[6].y);
    ar(boxVertices[6].z);
    ar(boxVertices[7].x);
    ar(boxVertices[7].y);
    ar(boxVertices[7].z);

    ar(tiles);

    setupCube();
}

template<class Archive>
void SquareTile::serialize(Archive &ar) {
    ar(cereal::base_class<Tile>(this));
    ar(vert1.x);
    ar(vert1.y);
    ar(vert1.z);
    ar(vert2.x);
    ar(vert2.y);
    ar(vert2.z);
    ar(vert3.x);
    ar(vert3.y);
    ar(vert3.z);
    ar(vert4.x);
    ar(vert4.y);
    ar(vert4.z);
    updateVertex();
}

template<class Archive>
void Texture::save(Archive &ar) const {
    ar(type);
    ar(path.data);
}

template<class Archive>
void Texture::load(Archive &ar) {
    ar(type);
    ar(path.data);
    newTexture(*this, path.data, type.c_str());
}

template<class Archive>
void TileWrapper::serialize(Archive &ar) {
    ar(type);
    ar(active);
    ar(*t);
}

template<class Archive>
void Tile::serialize(Archive &ar) {
    ar(name);
    ar(textureScale);
    ar(textureRotation);
    ar(texturePosition.x);
    ar(texturePosition.y);
    ar(texture);
}
