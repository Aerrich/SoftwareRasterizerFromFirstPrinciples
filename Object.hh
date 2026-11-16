//
// Created by erikz on 13.11.2026.
//

#pragma once
#include "Mesh.hh"

class Object {

public:

    Object(Mesh mesh);
    Object(Mesh mesh, Vec3<float> position);
    Object(Mesh mesh, Mat4<float> transform);

    void transform(Mat4<float> transform);
    void moveTo(Vec3<float> position);
    Mesh& getMesh();
    Mat4<float> getTransform();

private:

    Mesh mesh;
    Mat4<float> objectTransform;


};
