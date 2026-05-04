#include "cursorMovment.hpp"
#include <windows.h>

void cursorMovment::moveCursor(int x, int y) {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    int absoluteX = (x / width) * 65536;
    int absoluteY = (y / height) * 65536;
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;         
    input.mi.dy = y;         
    input.mi.dwFlags = MOUSEEVENTF_MOVE; 

    SendInput(1, &input, sizeof(INPUT));
}