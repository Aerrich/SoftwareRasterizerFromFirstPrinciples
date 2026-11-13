cmake_minimum_required(VERSION 4.3)
project(SoftwareRasterizerFromFirstPrinciple)

set(CMAKE_CXX_STANDARD 20)

add_executable(SoftwareRasterizerFromFirstPrinciple
        main.cpp
        Mesh.cpp
        Mesh.hh
        Math.hh
        Window.cpp
        Window.hh
        Camera.cpp
        Camera.hh
        Object.cpp
        Object.hh)


add_executable(Tests
        test.cpp)