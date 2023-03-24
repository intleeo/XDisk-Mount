#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    const char CLASS_NAME[] = "My Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "X Disk",                    // Window text
        WS_OVERLAPPED | WS_SYSMENU,            // Window style
        100, 100, 100, 130, // 位置为 (100, 100)，宽度为 400，高度为 300
        // Size and position
        //CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Parse the command line
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    // Check for command line arguments
    if (argc > 1)
    {
        if (wcscmp(argv[1], L"/m") == 0)
        {
            system("net use X: \\\\10.16.129.56\\tools\\pack \"woshililei4613@\" /user:lilei-hj");
            PostQuitMessage(0);
        }
        else if (wcscmp(argv[1], L"/d") == 0)
        {
            system("net use * /delete /y");
            PostQuitMessage(0);
        }
        else
        {
            // Invalid argument
            MessageBox(hwnd, "Invalid argument", "Error", MB_OK | MB_ICONERROR);
        }
    }

    // Create the buttons
    CreateWindow("BUTTON", "挂载X盘", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    CreateWindow("BUTTON", "删除X盘", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 50, 100, 30, hwnd, (HMENU)2, hInstance, NULL);

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1:
            system("net use X: \\\\10.16.129.56\\tools\\pack \"woshililei4613@\" /user:lilei-hj");
            break;
        case 2:
            system("net use * /delete /y");
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
