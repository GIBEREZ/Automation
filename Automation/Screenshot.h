#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <opencv2/opencv.hpp>
#include <Windows.h>

#include "Enumeration.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class Screenshot
{
public:
	// �����ͼ
	static bool Screen(HWND hwnd, cv::Mat* imagePtr);
	// ȫ����ͼ
	static Ment GetFullScreen(HWND hwnd, cv::Mat& buffer);
	// ���ڽ�ͼ
	static Ment GetWindowScreen(HWND hwnd, cv::Mat& buffer);
	// ������ͼ
	static int ContinuousScreenshots(int S, char title[MAX_PATH]);
};

class Identify
{
public:
	static bool matching(const cv::Mat& img, const cv::Mat& temp, int& X, int& Y);
};

#endif 