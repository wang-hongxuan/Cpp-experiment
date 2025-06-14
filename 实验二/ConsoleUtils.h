//
// Created by wanghongxuan on 25-5-20.
//

#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

inline void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif // CONSOLE_UTILS_H