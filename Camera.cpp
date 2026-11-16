//
// Created by erikz on 13.11.2026.
//
#include "Camera.hh"


Camera::Camera(Vec3<float> position, Vec3<float> lookAt, Vec3<float> up, float fov, float nearPlane, float farPlane)
:position(position), lookAt(lookAt), up(up), nearPlane(nearPlane), farPlane(farPlane), fov(fov)
{

}

Camera::Camera(Vec3<float> position, Vec3<float> lookAt, Vec3<float> up)
:position(position), lookAt(lookAt), up(up){

    fov = 1.55f;
    nearPlane = 1.0f;
    farPlane = 10.0f;

}




Mat4<float> Camera::getViewMatrix() {

    Vec3<float> cross = up % lookAt;

    Mat4<float> rotation{
    {
            {cross.x, cross.y, cross.z, 0},
            {up.x, up.y, up.z, 0},
            {lookAt.x, lookAt.y, lookAt.z, 0},
            {0, 0, 0, 1}
        }
    };

    Mat4<float> translation{
        {
            {1, 0, 0, -position.x},
            {0, 1, 0, -position.y},
            {0, 0, 1, -position.z},
            {0, 0, 0, 1}
        }
    };

    return rotation * translation;

}

Mat4<float> Camera::getProjectionMatrix() {
    return Mat4<float>{
        {
            {fov, 0, 0, 0},
            {0, fov, 0, 0},
            {0, 0, (farPlane / (farPlane - nearPlane)), -(farPlane * nearPlane) / (farPlane - nearPlane)},
            {0, 0, 1, 0}
        }
    };
}

float Camera::getFarPlane() {
    return farPlane;
}

float Camera::getNearPlane() {
    return nearPlane;
}