#include <windows.h>

const wchar_t CLASS_NAME[] = L"GTAIdlerWindow";
HFONT hDefaultFont = NULL;
HBRUSH hBrushWhite = NULL;
HICON hIcon = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                PostQuitMessage(0);
                return 0;
            }
            if (LOWORD(wParam) == 2) {
                DWORD attrib = GetFileAttributesW(L"gta_sa.exe");
                if (attrib == INVALID_FILE_ATTRIBUTES || (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
                    MessageBoxW(hwnd, L"gta_sa.exe not found!", L"Error", MB_OK | MB_ICONERROR);
                } else {
                    ShellExecuteW(hwnd, L"open", L"gta_sa.exe", NULL, NULL, SW_SHOWNORMAL);
                    PostQuitMessage(0);
                }
                return 0;
            }
            break;
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wParam;
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(0, 0, 0));
            return (INT_PTR)hBrushWhite;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow) {
    hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
    if (hBrushWhite == NULL) {
        MessageBoxW(NULL, L"Failed to create background brush!", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
    hDefaultFont = CreateFontIndirect(&ncm.lfMessageFont);
    if (hDefaultFont == NULL) {
        MessageBoxW(NULL, L"Failed to create font!", L"Error", MB_OK | MB_ICONERROR);
        DeleteObject(hBrushWhite);
        return 0;
    }

    hIcon = (HICON)LoadImage(
        hInstance,
        MAKEINTRESOURCE(101),
        IMAGE_ICON,
        16, 16,
        0
    );
    if (hIcon == NULL) {
        MessageBoxW(NULL, L"Failed to load embedded icon! Using default icon.", L"Warning", MB_OK | MB_ICONWARNING);
        hIcon = LoadIcon(NULL, IDI_APPLICATION);
        if (hIcon == NULL) {
            MessageBoxW(NULL, L"Failed to load default icon!", L"Error", MB_OK | MB_ICONERROR);
            DeleteObject(hBrushWhite);
            DeleteObject(hDefaultFont);
            return 0;
        }
    }

    const wchar_t* labelText = L"Idling Grand Theft Auto: San Andreas from Steam";
    HDC hdc = GetDC(NULL);
    SelectObject(hdc, hDefaultFont);
    SIZE textSize;
    GetTextExtentPoint32W(hdc, labelText, wcslen(labelText), &textSize);
    ReleaseDC(NULL, hdc);

    int iconWidth = 16;
    int gap = 5;
    int labelWidth = textSize.cx;
    int padding = 44;
    int windowWidth = iconWidth + gap + labelWidth + 2 * padding;
    int windowHeight = 150;

    int xPos = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

    WNDCLASSW wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = hBrushWhite;
    wc.hIcon = hIcon;

    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Failed to register window class!", L"Error", MB_OK | MB_ICONERROR);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"GTA SA Steam Idler",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        xPos, yPos, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );
    if (hwnd == NULL) {
        MessageBoxW(NULL, L"Failed to create window!", L"Error", MB_OK | MB_ICONERROR);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }

    int contentWidth = iconWidth + gap + labelWidth;
    int iconX = (windowWidth - contentWidth) / 2;
    int labelX = iconX + iconWidth + gap;
    int contentHeight = 40 + 10 + 30;
    int contentY = (windowHeight - contentHeight) / 2;
    
    int buttonWidth = 100;
    int buttonHeight = 30;
    int gapBetweenButtons = 10;
    int totalButtonsWidth = 2 * buttonWidth + gapBetweenButtons;
    int buttonsStartX = (windowWidth - totalButtonsWidth) / 2;
    int buttonY = contentY + 40 + 10;

    HWND hButtonLaunch = CreateWindowW(
        L"BUTTON",
        L"Launch",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        buttonsStartX, buttonY, buttonWidth, buttonHeight,
        hwnd, (HMENU)2, hInstance, NULL
    );
    if (hButtonLaunch == NULL) {
        MessageBoxW(NULL, L"Failed to create launch button!", L"Error", MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }
    SendMessage(hButtonLaunch, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);

    HWND hButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        buttonsStartX + buttonWidth + gapBetweenButtons, buttonY, buttonWidth, buttonHeight,
        hwnd, (HMENU)1, hInstance, NULL
    );
    if (hButton == NULL) {
        MessageBoxW(NULL, L"Failed to create button!", L"Error", MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }
    SendMessage(hButton, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);

    HWND hIconStatic = CreateWindowW(
        L"STATIC", NULL,
        WS_CHILD | WS_VISIBLE | SS_ICON | SS_CENTERIMAGE,
        iconX, contentY, iconWidth, 16,
        hwnd, NULL, hInstance, NULL
    );
    if (hIconStatic == NULL) {
        MessageBoxW(NULL, L"Failed to create icon static control!", L"Error", MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }
    SendMessage(hIconStatic, STM_SETICON, (WPARAM)hIcon, 0);

    HWND hLabel = CreateWindowW(
        L"STATIC",
        labelText,
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        labelX, contentY, labelWidth, 40,
        hwnd, NULL, hInstance, NULL
    );
    if (hLabel == NULL) {
        MessageBoxW(NULL, L"Failed to create label!", L"Error", MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        DeleteObject(hBrushWhite);
        DeleteObject(hDefaultFont);
        DestroyIcon(hIcon);
        return 0;
    }
    SendMessage(hLabel, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hBrushWhite);
    DeleteObject(hDefaultFont);
    DestroyIcon(hIcon);
    return 0;
}