//
// Created by erikz on 18.07.2026.
//
#define UNICODE
#include "Window.hh"


namespace SR {
    uint32_t getRGB(unsigned char r, unsigned char g, unsigned char b)
    {
        return r << 16 | g << 8 | b;
    }

    void Window::putPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    {
        buffer.pixels[y * buffer.width + x] = getRGB(r,g,b);
    }

    float Window::getDepth(int x, int y) {
        return buffer.depth[y * buffer.width + x];
    }

    void Window::setDepth(int x, int y, float depth) {
        buffer.depth[y * buffer.width + x] = depth;
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