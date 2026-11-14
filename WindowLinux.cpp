//
// Created by erikzygmanowski on 11/13/26.
//

#include "Window.hh"
#include <stdexcept>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <iostream>
namespace SR {
    Window::Window(int width, int height)
    :width(width), height(height){

        display = XOpenDisplay(nullptr);
        if (!display)
            throw std::runtime_error("Cannot connect to X server");

        screen = DefaultScreen(display);

        handle = XCreateSimpleWindow(
            display,
            RootWindow(display, screen),
            0, 0,           // Position
            1080, 720,      // Size
            0,              // Border width
            BlackPixel(display, screen),
            BlackPixel(display, screen)
        );

        XStoreName(display, handle, "Software Rasterizer");
        XSelectInput(display, handle, ExposureMask | StructureNotifyMask);
        XMapWindow(display, handle);
        XFlush(display);

        gc = XCreateGC(display, handle, 0, nullptr);
        image = XCreateImage(
            display,
            DefaultVisual(display, screen),
            DefaultDepth(display, screen),
            ZPixmap,
            0,
            nullptr,
            width,
            height,
            32,
            0);




        buffer.width = width;
        buffer.height = height;

        buffer.pixels.resize(width * height);

    }

    void Window::redraw() {

        image->data = (char*)std::calloc(
                height, image->bytes_per_line
                    );

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int srcX = x * buffer.width / width;
                int srcY = y * buffer.height / height;

                XPutPixel(image, x, y,
                          buffer.pixels[srcY * buffer.width + srcX]);
            }
        }

        XPutImage(
            display,        // Connection to the X server
            handle,         // Destination window
            gc,             // Graphics context
            image,          // Source XImage*
            0, 0,           // Starting x, y within the image
            0, 0,           // Destination x, y within the window
            width,   // Number of pixels to copy horizontally
            height   // Number of pixels to copy vertically
        );

        XFlush(display);
    }

    XEvent ev;
    bool Window::processEvents() {
        while (XPending(display) > 0) {
            XNextEvent(display, &ev);

            switch(ev.type) {
                case Expose:
                    if (ev.xexpose.count == 0)
                        redraw();
                    break;
                case ConfigureNotify: {
                    int newWidth = ev.xconfigure.width;
                    int newHeight = ev.xconfigure.height;

                    if (newWidth != width || newHeight != height) {
                        XDestroyImage(image);

                        width = newWidth;
                        height = newHeight;

                        image = XCreateImage(
                        display,
                        DefaultVisual(display, screen),
                        DefaultDepth(display, screen),
                        ZPixmap,
                        0,
                        nullptr,
                        width,
                        height,
                        32,
                        0);

                    }
                    break;
                }
                default:
                    return true;
                    break;
            }
        }
        return true;

    }

    void Window::close() {
        XDestroyImage(image);
        XFreeGC(display, gc);
        XDestroyWindow(display, handle);
        XCloseDisplay(display);
    }

}
