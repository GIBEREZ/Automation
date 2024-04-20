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
    // ��ӡ������пɼ����㴰�ڵı���
    static BOOL CALLBACK WEnumProcess(HWND hwnd, LPARAM lParam);
    // �����û�����ǰ�������Ķ��㴰�ھ��
    static HWND GetActiveWindowHandle();
    // ���ݱ����ȡ������ú����������жϾ���Ƿ����
    static HWND GetHandle(const std::string& windowTitle);
    // ���ݾ���Ĵ���λ�ý������������
    static Ment MouseClick(HWND hwnd, int x, int y);
    // ���ݾ�����л����þ���Ĵ���Ϊǰ������
    static Ment SwitchWindow(HWND hwnd);
};

class FuncTool
{
public:
    static void ClickDelay();
};

#endif
