//
// Created by erikz on 18.07.2026.
//
#define UNICODE
#include "Window.hh"


namespace SR {
    uint32_t getRGB(int r, int g, int b)
    {
        return r << 16 | g << 8 | b;
    }

    void Window::putPixel(int x, int y, int r, int g, int b)
    {
        buffer.pixels[y * buffer.width + x] = getRGB(r,g,b);
    }

    int Window::getWidth()
    {
        return buffer.width;
    }

    int Window::getHeight()
    {
        return buffer.height;
    }

}