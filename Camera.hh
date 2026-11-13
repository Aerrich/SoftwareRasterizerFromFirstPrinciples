//
// Created by erikz on 13.11.2026.
//

#pragma once

#include "Math.hh"

class Camera {

    public:

    Camera(Vec3<float> position, Vec3<float> lookAt, Vec3<float> up);

    Mat4<float> getViewMatrix();


    private:

    Vec3<float> position;
    Vec3<float> lookAt;
    Vec3<float> up;


};
