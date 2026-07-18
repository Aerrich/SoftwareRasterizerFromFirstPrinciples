//
// Created by erikz on 18.07.2026.
//

#ifndef SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_WINDOW_HH
#define SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_WINDOW_HH
#include <cstdint>
#include <Windows.h>
#include <vector>

struct frameBuffer
{
    int width;
    int height;
    std::vector<std::uint32_t> pixels;
};

class Window
{
public:
    Window(HINSTANCE hInstance, int cmdshow, int width, int height);
    Window();

    int getWidth();
    int getHeight();
    void redraw();
    void putPixel(int x, int y, int r, int g, int b);

private:

    int width;
    int height;
    HWND hwnd;

    static LRESULT CALLBACK WindowProc(HWND hwnd, const UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void OnSize(HWND hwnd, UINT flag, int newWidth, int newHeight);

    frameBuffer buffer;


};


#endif //SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_WINDOW_HH
