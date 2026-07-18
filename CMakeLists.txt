cmake_minimum_required(VERSION 4.3)
project(SoftwareRasterizerFromFirstPrinciple)

set(CMAKE_CXX_STANDARD 20)

add_executable(SoftwareRasterizerFromFirstPrinciple main.cpp
        Object.cpp
        Object.hh
        Math.hh
        Window.cpp
        Window.hh)
