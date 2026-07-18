//
// Created by erikz on 18.07.2026.
//

#ifndef SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_MATH_HH
#define SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_MATH_HH

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
    float operator *(const Vec2& v)
    {
        return x * v.x + y * v.y;
    }
    float operator %(const Vec2& v)
    {
        return x * v.y - y * v.x;
    }

};


template <typename T>
struct Vec3
{
    T x, y, z;

    Vec3 operator +(const Vec3& v)
    {
        return Vec2(x + v.x, y + v.y, z + v.z);
    }
    Vec3 operator -(const Vec3& v)
    {
        return Vec2(x - v.x, y - v.y, z - v.z);
    }
    float operator *(const Vec3& v)
    {
        return x * v.x + y * v.y + z * v.z;
    }
    Vec3 operator %(const Vec3& v)
    {
        T xC =y * v.z - z * v.y;
        T yC =z * v.x - x * v.z;
        T zC = x * v.y - y * v.x;
        return {xC,yC,zC};
    }

};


#endif //SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_MATH_HH
