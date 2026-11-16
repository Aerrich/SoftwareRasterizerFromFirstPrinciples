//
// Created by erikz on 13.11.2026.
//

#include "Object.hh"




Object::Object(Mesh mesh)
:mesh(mesh) {

    objectTransform = Mat4<float>::identity();

}

Object::Object(Mesh mesh, Vec3<float> position)
:mesh(mesh) {

    objectTransform = Mat4<float>::identity();
    objectTransform[0][3] = position.x;
    objectTransform[1][3] = position.y;
    objectTransform[2][3] = position.z;

}

Object::Object(Mesh mesh, Mat4<float> transform)
:mesh(mesh), objectTransform(transform) {
}

void Object::transform(Mat4<float> transform) {

    transform = transform * objectTransform;

}

void Object::moveTo(Vec3<float> position) {

    objectTransform[0][3] = position.x;
    objectTransform[1][3] = position.y;
    objectTransform[2][3] = position.z;

}

Mesh& Object::getMesh() {
    return mesh;
}

Mat4<float> Object::getTransform() {
    return objectTransform;
}