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

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(X11 REQUIRED)
    target_link_libraries(
            SoftwareRasterizerFromFirstPrinciple
            PRIVATE X11::X11
    )
endif()

if(WIN32)
    target_sources(SoftwareRasterizerFromFirstPrinciple
            PRIVATE WindowWin32.cpp)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(SoftwareRasterizerFromFirstPrinciple
            PRIVATE WindowLinux.cpp)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()


add_executable(Tests
        test.cpp)


configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Cube.obj"
        "${CMAKE_CURRENT_BINARY_DIR}/Cube.obj"
        COPYONLY
)