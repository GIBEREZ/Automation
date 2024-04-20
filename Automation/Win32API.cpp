#include "Win32API.h"
#include <thread>

/*
 * ��ȡǰ������ڵĶ��㴰�ھ��
 * @param HWND ���ھ��
 * @param LPARAM ���ݸ��ص������Ķ���ֵ
 * @return �ûص�����һֱö����FALSE
 */
BOOL CALLBACK WinTool::WEnumProcess(HWND hwnd, LPARAM lParam)
{
    if (!IsWindowVisible(hwnd)) {
        return TRUE;
    }
    char w_title[MAX_PATH], w_class[MAX_PATH];
    RECT W_pos;
    // ��ȡ���ڱ���
    GetWindowText(hwnd, w_title, MAX_PATH);
    // ��ȡ��������
    GetClassName(hwnd, w_class, MAX_PATH);
    // ��ȡ����λ����Ϣ
    GetWindowRect(hwnd, &W_pos);
    if (strlen(w_title) != 0) {
        std::cout << "����:" << "[" << w_title << "]" << std::endl;
    }
    return TRUE;  // ���� TRUE ����ö�٣����� FALSE ֹͣö��
}

/*
 * ��ȡǰ������ڵĶ��㴰�ھ��
 * @return HWND ���
 */
HWND WinTool::GetActiveWindowHandle()
{
    // ��ȡ�û�ǰ�����ھ��
    HWND foregroundWindow = GetForegroundWindow();
    HWND topLevelWindow = NULL;
    // ����������ȡǰ�����ڵĶ��㴰�ھ��
    if (foregroundWindow)
    {
        topLevelWindow = GetAncestor(foregroundWindow, GA_ROOT);
    }

    return topLevelWindow;
}


/*
 * ���Ҹ����ݵı���һ�µĴ��ھ��
 * @param std::string �������
 * @return HWND ���
 */
HWND WinTool::GetHandle(const std::string& windowTitle)
{
    return FindWindow(nullptr, windowTitle.c_str());
}

/*
 * ���ݾ���Ĵ���λ�ý������������
 * @param HWND ���ھ��
 * @param x x������
 * @param y y������
 * @return Ment ״̬��
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
        std::cout << "�������Ч" << std::endl;
        return error;
    }
    return ok;
}
/*
 * ���ݾ�����л����þ���Ĵ���Ϊǰ������
 * @param HWND ���ھ��
 * @return Ment ״̬��
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
