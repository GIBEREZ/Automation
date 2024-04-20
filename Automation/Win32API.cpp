#include "Win32API.h"
#include <thread>

/*
 * 获取前景活动窗口的顶层窗口句柄
 * @param HWND 窗口句柄
 * @param LPARAM 传递给回调函数的定义值
 * @return 该回调函数一直枚举至FALSE
 */
BOOL CALLBACK WinTool::WEnumProcess(HWND hwnd, LPARAM lParam)
{
    if (!IsWindowVisible(hwnd)) {
        return TRUE;
    }
    char w_title[MAX_PATH], w_class[MAX_PATH];
    RECT W_pos;
    // 获取窗口标题
    GetWindowText(hwnd, w_title, MAX_PATH);
    // 获取窗口类名
    GetClassName(hwnd, w_class, MAX_PATH);
    // 获取窗口位置信息
    GetWindowRect(hwnd, &W_pos);
    if (strlen(w_title) != 0) {
        std::cout << "标题:" << "[" << w_title << "]" << std::endl;
    }
    return TRUE;  // 返回 TRUE 继续枚举，返回 FALSE 停止枚举
}

/*
 * 获取前景活动窗口的顶层窗口句柄
 * @return HWND 句柄
 */
HWND WinTool::GetActiveWindowHandle()
{
    // 获取用户前景窗口句柄
    HWND foregroundWindow = GetForegroundWindow();
    HWND topLevelWindow = NULL;
    // 如果存在则获取前景窗口的顶层窗口句柄
    if (foregroundWindow)
    {
        topLevelWindow = GetAncestor(foregroundWindow, GA_ROOT);
    }

    return topLevelWindow;
}


/*
 * 查找跟传递的标题一致的窗口句柄
 * @param std::string 句柄标题
 * @return HWND 句柄
 */
HWND WinTool::GetHandle(const std::string& windowTitle)
{
    return FindWindow(nullptr, windowTitle.c_str());
}

/*
 * 根据句柄的窗口位置进行鼠标左键点击
 * @param HWND 窗口句柄
 * @param x x轴坐标
 * @param y y轴坐标
 * @return Ment 状态码
 */
Ment WinTool::MouseClick(HWND hwnd, int x, int y)
{
    RECT rect;
    GetWindowRect(hwnd, &rect);
    x = rect.left + x;
    y = rect.top + y;

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

    SetCursorPos(x, y);

    if (SendInput(1, &input, sizeof(INPUT)) == 0)
    {
        std::cout << "鼠标点击无效" << std::endl;
        return error;
    }
    return ok;
}
/*
 * 根据句柄，切换出该句柄的窗口为前景窗口
 * @param HWND 窗口句柄
 * @return Ment 状态码
 */
Ment WinTool::SwitchWindow(HWND hwnd)
{
    if (BringWindowToTop(hwnd) && SetForegroundWindow(hwnd))
        return ok;
    return error;
}

void FuncTool::ClickDelay()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
