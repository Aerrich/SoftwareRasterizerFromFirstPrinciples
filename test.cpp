//
// Created by erikz on 13.11.2026.
//
#include <iostream>
#include "Math.hh"

int main()
{
    std::cout << "Running math tests\n";

    Mat4<float> a{
        {
            { 1,  2,  3,  4},
            { 5,  6,  7,  8},
            { 9, 10, 11, 12},
            {13, 14, 15, 16}
        }
    };

    Mat4<float> b{
        {
            { 1,  0,  0,  0},
            { 0,  1,  0,  0},
            { 0,  0,  1,  0},
            { 0,  0,  0,  1}
        }
    };

    Mat4<float> res = a * b;


    std::cout << res;


    Vec4<float> c{1,1,1,1};

    Vec4<float> resVec = b * c;

    std::cout << resVec << " ";


    return 0;
}