//
// Created by erikz on 13.11.2026.
//

#pragma once

#include "Math.hh"

class Camera {

    public:

    Camera(Vec3<float> position, Vec3<float> lookAt, Vec3<float> up);
    Camera(Vec3<float> position, Vec3<float> lookAt, Vec3<float> up, float fov, float nearPlane, float farPlane);

    Mat4<float> getViewMatrix();
    Mat4<float> getProjectionMatrix();

    float getNearPlane();
    float getFarPlane();

    private:

    Vec3<float> position;
    Vec3<float> lookAt;
    Vec3<float> up;

    float fov;
    float nearPlane;
    float farPlane;
    float aspect;



};
