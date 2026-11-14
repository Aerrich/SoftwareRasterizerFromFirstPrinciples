//
// Created by erikz on 18.07.2026.
//

#pragma once

#include <cstdint>
#include <vector>
#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__)
    #include <X11/Xlib.h>
#endif


struct frameBuffer
{
    int width;
    int height;
    std::vector<std::uint32_t> pixels;
};


namespace SR {
    class Window
    {
    public:
        Window(int width, int height);

        int getWidth();
        int getHeight();
        void redraw();
        void putPixel(int x, int y, int r, int g, int b);

        void close();

        bool processEvents();

    private:

        int width;
        int height;

        frameBuffer buffer;

#if defined(_WIN32)
        HWND handle;
#elif defined(__linux__)
        Display* display;
        ::Window handle;
        GC gc;
        XImage* image;
        int screen;
#endif

    };
}

