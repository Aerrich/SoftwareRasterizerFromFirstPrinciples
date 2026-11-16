//
// Created by erikz on 18.07.2026.
//
#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>



//TODO SIMD optimization


template <typename T>
struct Vec2
{
    T x, y;

    Vec2 operator +(const Vec2& v)
    {
        return Vec2(x + v.x, y + v.y);
    }
    Vec2 operator -(const Vec2& v)
    {
        return Vec2(x - v.x, y - v.y);
    }
    T operator *(const Vec2& v)
    {
        return x * v.x + y * v.y;
    }
    Vec2 operator *(const T& s) {
        return Vec2(x * s, y * s);
    }
    Vec2 operator /(const T& s) {
        return Vec2(x / s, y / s);
    }
    T operator %(const Vec2& v)
    {
        return x * v.y - y * v.x;
    }

    T length() {
        return sqrt(x * x + y * y);
    }

    Vec2 normalize() {
        T vLength = length();
        T xN = x / vLength;
        T yN = y / vLength;
        return {xN, yN};
    }

};


template <typename T>
struct Vec3
{
    T x, y, z;

    Vec3 operator +(const Vec3& v)
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3 operator -(const Vec3& v)
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    T operator *(const Vec3& v)
    {
        return x * v.x + y * v.y + z * v.z;
    }
    Vec3 operator *(const T& s) {
        return Vec3(x * s, y * s, z * s);
    }
    Vec3 operator /(const T& s) {
        return Vec3(x / s, y / s, z / s);
    }
    Vec3 operator %(const Vec3& v)
    {
        T xC =y * v.z - z * v.y;
        T yC =z * v.x - x * v.z;
        T zC = x * v.y - y * v.x;
        return {xC,yC,zC};
    }

    T length() {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() {
        T vLength = length();
        T xN = x / vLength;
        T yN = y / vLength;
        T zN = z / vLength;
        return {xN, yN, zN};
    }

};


template <typename T>
struct Vec4
{
    T x, y, z, w;

    Vec4() : x{}, y{}, z{}, w{} {}

    Vec4(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w) {}

    Vec4(Vec3<T> v, T f) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = f;
    }

    T& operator[](std::size_t i) {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("Vec4 index must be between 0 and 3");
        }
    }

    Vec4 operator +(const Vec4& v)
    {
        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    Vec4 operator -(const Vec4& v)
    {
        return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    T operator *(const Vec4& v)
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
    Vec4 operator *(const T& s) {
        return Vec4(x * s, y * s, z * s, w * s);
    }
    Vec4 operator /(const T& s) {
        return Vec4(x / s, y / s, z / s, w / s);
    }
    Vec4 operator %(const Vec4& v)
    {
        T xC =y * v.z - z * v.y;
        T yC =z * v.x - x * v.z;
        T zC = x * v.y - y * v.x;
        T wC = x * v.z - z * v.x;
        return {xC,yC,zC,wC};
    }

    T length() {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Vec4 normalize() {
        T vLength = length();
        T xN = x / vLength;
        T yN = y / vLength;
        T zN = z / vLength;
        T wN = w / vLength;
        return {xN, yN, zN, wN};
    }

};

template <typename T>
std::ostream& operator <<(std::ostream& out, const Vec4<T>& v) {
    out << v.x << " " << v.y << " " << v.z << " " << v.w;
    return out;
}

template <typename T>
struct Mat4 {

    T m[4][4];

    static Mat4<T> identity() {
        return Mat4<T>{
            {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            }};
    }

    T* operator[](std::size_t i) {
        if (i >= 4)
            throw std::out_of_range("Mat4 row index out of range");

        return m[i];
    }

    Vec4<T> row(int i) const{
        return Vec4<T>(m[i][0], m[i][1], m[i][2], m[i][3]);
    }

    Vec4<T> col(int i) const{
        return Vec4<T>(m[0][i], m[1][i], m[2][i], m[3][i]);
    }

    Mat4<T> operator *(const Mat4& x) const
    {

        Mat4<T> result;

        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                result.m[i][j] = row(i) * x.col(j);
            }
        }

        return result;

    }

    Vec4<T> operator *(const Vec4<T>& x) {

        Vec4<T> result;

        for (int i=0; i<4; i++) {
            result[i] = row(i) * x;
        }

        return result;

    }

};

template <typename T>
std::ostream& operator <<(std::ostream& out, Mat4<T>& v) {
    out << std::fixed << std::setprecision(3);
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            out << std::right << std::setw(10) << v[i][j]; // One padded element
        }
        out << "\n";
    }
    return out;
}