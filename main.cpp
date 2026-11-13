#define UNICODE

#include <format>
#include <iostream>
#include <windows.h>
#include "Mesh.hh"
#include "Window.hh"
#include "Camera.hh"
#include <vector>
#include "Object.hh"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    Window window{hInstance, cmdshow, 1080, 720};

    for (int x = 0; x < window.getWidth(); x++)
    {
        for (int y = 0; y < window.getHeight(); y++)
        {
            window.putPixel(x,y,0,0,255);
        }
    }

    std::vector<Object> objects;

    Mesh cube("G:/projects/SoftwareRasterizerFromFirstPrinciples/Cube.obj");

    Object cube1(cube);

    objects.push_back(cube1);



    Camera camera{{0,0,-5}, {0,0,1}, {0,1,0}};

    Mat4<float> viewMatrix = camera.getViewMatrix();

    

    window.putPixel(20,20,0,255,0);

    window.redraw();

    MSG msg{};

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
