#include <iostream>
#include <Windows.h>
#include <thread>
#include <functional>
#include <string>
#include <opencv2/opencv.hpp>

#include "XML_Parsing.h"
#include "Win32API.h"
#include "Business.h"

// 模板匹配测试
void mbpp()
{
    cv::Mat img = cv::imread("2.png");
    std::cout << "Image: " << img.cols << "x" <<img.rows << std::endl;
    std::cout << "Number of Channels: " << img.channels() << std::endl;
    std::cout << "Pixel Depth: " << img.type() << std::endl;
    cv::Mat temp = cv::imread("Image/logo.png");
    std::cout << "Image: " << temp.cols << "x" << temp.rows << std::endl;
    std::cout << "Number of Channels: " << temp.channels() << std::endl;
    std::cout << "Pixel Depth: " << temp.type() << std::endl;
    int X = 0;
    int Y = 0;
    Identify::matching(img, temp, X, Y);
}

void click()
{
    WinTool::MouseClick(WinTool::GetHandle("MuMu模拟器12"), 610,784);
}

void scree()
{
    WinTool::SwitchWindow(WinTool::GetHandle("MuMu模拟器12"));
    cv::Mat img;
    Screenshot::Screen(WinTool::GetHandle("MuMu模拟器12") ,&img);
    cv::cvtColor(img, img, cv::COLOR_RGBA2RGB);
    cv::imwrite("2.png", img);
}

void user()
{
    while (true)
    {
        std::string input;
        std::cout << "#=======#任务#=======#\n 1：模板匹配\n 2：截图\n 3：输出所有窗口句柄标题\n运行：";
        std::cin >> input;
        if (input == "quit")
        {
            break;
        }
        else if (input == "1")
        {
            mbpp();
        }
        else if (input == "2")
        {
            scree();
        }
        else if (input == "3")
        {
            EnumWindows(WinTool::WEnumProcess, 0);
        }
    }
}

int main()
{
    user();

    return 0;

    WinTool::SwitchWindow(WinTool::GetHandle("MuMu模拟器12"));

    std::this_thread::sleep_for(std::chrono::seconds(3));

    EnumWindows(WinTool::WEnumProcess, 0);

    // MuMu模拟器12
    std::cout << "\n" << std::endl;

    OutputDebugStringA("启动\n");
    task T = task();
    T.task_init("A1");

    business* b = new business(WinTool::GetHandle("MuMu模拟器12"));

    std::thread t1([b]() { b->ScreenThread(); });
    std::thread t2([b](task& obj) { b->service(obj); }, std::ref(T));

    t1.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    t2.join();

    return 0;
}