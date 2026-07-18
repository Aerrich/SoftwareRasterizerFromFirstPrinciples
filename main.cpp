#define UNICODE

#include <format>
#include <iostream>
#include <windows.h>
#include "Object.hh"
#include "Window.hh"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{

    Window window{hInstance, cmdshow, 1080, 720};

    for (int x = 0; x < window.getWidth(); x++)
    {
        for (int y = 0; y < window.getHeight(); y++)
        {
            window.putPixel(x,y,0,0,255);
        }
    }

    Object cube("C:/Users/erikz/Desktop/Cube.obj");

    OutputDebugStringA(cube.toString().c_str());

    Vec2 a = {window.getWidth()/2,0};
    Vec2 b = {0,window.getHeight()-1};
    Vec2 c = {window.getWidth(),window.getHeight()-1};


    for (int x = 0; x < window.getWidth(); x++)
    {
        for (int y = 0; y < window.getHeight(); y++)
        {
            Vec2 p = {x, y};

            Vec2 AB = b-a;
            Vec2 AP = p-a;

            Vec2 BC = c-b;
            Vec2 BP = p-b;

            Vec2 CA = a-c;
            Vec2 CP = p-c;

            float cross1 = AB%AP;
            float cross2 = BC%BP;
            float cross3 = CA%CP;

            if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0))
            {
                window.putPixel(x,y,255,255, 0);
            }
        }
    }

    window.redraw();

    MSG msg{};

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}