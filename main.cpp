#define UNICODE

#include <format>
#include <iostream>
#include "Mesh.hh"
#include "Window.hh"
#include "Camera.hh"
#include <vector>
#include "Object.hh"

int main() {
    SR::Window window{1080, 720};

    for (int x = 0; x < window.getWidth(); x++)
    {
        for (int y = 0; y < window.getHeight(); y++)
        {
            window.putPixel(x,y,0,0,255);
        }
    }

    std::vector<Object> objects;

    Mesh cube("Cube.obj");

    Object cube1(cube);

    objects.push_back(cube1);



    Camera camera{{0,0,-5}, {0,0,1}, {0,1,0}};

    Mat4<float> viewMatrix = camera.getViewMatrix();



    window.putPixel(20,20,0,255,0);

    char r = 0;
    char g = 0;
    char b = 0;

    while (window.processEvents())
    {

        for (int x = 0; x < window.getWidth(); x++)
        {
            for (int y = 0; y < window.getHeight(); y++)
            {
                window.putPixel(x,y,255,255,255);
                int res = (x-window.getWidth()/2 - r)*(x-window.getWidth()/2 - r)+(y-window.getHeight()/2)*(y-window.getHeight()/2);
                if (res < (200*200)) {
                    window.putPixel(x,y,255-res/200,g,b);
                }
            }
        }

        r++;



        window.redraw();
    }

    window.close();

    return 0;

}
