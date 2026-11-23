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
    std::vector<float> depth;
};


namespace SR {
    class Window
    {
    public:
        Window(int width, int height);

        int getWidth();
        int getHeight();
        void redraw();
        void putPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

        float getDepth(int x, int y);

        void setDepth(int x, int y, float depth);

        void close();

        bool processEvents();

    private:

        int width;
        int height;

        frameBuffer buffer;

#if defined(_WIN32)
        static LRESULT CALLBACK WindowProc(
        HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        LRESULT HandleMessage(
            HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

