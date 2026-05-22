#include "cursorMovment.hpp"
#include <windows.h>

void cursorMovment::moveCursor(int dx, int dy) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void cursorMovment::click(bool isLeft){
    if(isLeft == true){
        INPUT inputs[2] = {0};
    
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    
        SendInput(2, inputs, sizeof(INPUT));
    }else{
        INPUT inputs[2] = {0};
    
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    
        SendInput(2, inputs, sizeof(INPUT));
    }
    
}