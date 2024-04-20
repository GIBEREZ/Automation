#ifndef WIN32API_H
#define WIN32API_H

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#include "Enumeration.h"


class WinTool
{
public:
    // 打印输出所有可见顶层窗口的标题
    static BOOL CALLBACK WEnumProcess(HWND hwnd, LPARAM lParam);
    // 返回用户正在前景交互的顶层窗口句柄
    static HWND GetActiveWindowHandle();
    // 根据标题获取句柄，该函数需自行判断句柄是否存在
    static HWND GetHandle(const std::string& windowTitle);
    // 根据句柄的窗口位置进行鼠标左键点击
    static Ment MouseClick(HWND hwnd, int x, int y);
    // 根据句柄，切换出该句柄的窗口为前景窗口
    static Ment SwitchWindow(HWND hwnd);
};

class FuncTool
{
public:
    static void ClickDelay();
};

#endif
