//
// Created by erikz on 18.07.2026.
//
#define UNICODE
#include "Window.hh"



void Window::OnSize(HWND hwnd, UINT flag, int newWidth, int newHeight)
{
    // Handle resizing
    width = newWidth;
    height = newHeight;

    InvalidateRect(hwnd, nullptr, FALSE);
}


LRESULT CALLBACK Window::WindowProc(HWND hwnd, const UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    Window* window = nullptr;

    if (uMsg == WM_CREATE)
    {
        auto* create = reinterpret_cast<CREATESTRUCT*>(lParam);

        window = static_cast<Window*>(create->lpCreateParams);

        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else
    {
        window = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    return window->HandleMessage(hwnd, uMsg, wParam, lParam);

}



Window::Window(HINSTANCE hInstance, int cmdshow, int width, int height)
{

    this->width = width;
    this->height = height;

    buffer.width = width;
    buffer.height = height;

    buffer.pixels.resize(width * height);

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = Window::WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, buffer.width, buffer.height,

        nullptr,       // Parent window
        nullptr,       // Menu
        hInstance,  // Instance handle
        this        // Additional application data
        );

    if (hwnd == nullptr)
    {

    }

    this->hwnd = hwnd;
    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);


}

LRESULT Window::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SIZE:
        {
            int newWidth = LOWORD(lParam);  // Macro to get the low-order word.
            int newHeight = HIWORD(lParam); // Macro to get the high-order word.

            // Respond to the message:
            OnSize(hwnd, static_cast<UINT>(wParam), width, height);
            return 0;
        }
    break;

    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            //FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            BITMAPINFO info{};
            info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            info.bmiHeader.biWidth = buffer.width;
            info.bmiHeader.biHeight = -buffer.height;
            info.bmiHeader.biCompression = BI_RGB;
            info.bmiHeader.biPlanes = 1;
            info.bmiHeader.biBitCount = 32;


            StretchDIBits(
                hdc,
                0,
                0,
                width,
                height,
                0,
                0,
                buffer.width,
                buffer.height,
                buffer.pixels.data(),
                &info,
                DIB_RGB_COLORS,
                SRCCOPY
            );

            EndPaint(hwnd, &ps);
            return 0;
        }
    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

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

void Window::redraw()
{
    InvalidateRect(hwnd, nullptr, TRUE);
}
