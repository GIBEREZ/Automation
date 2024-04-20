#include "Screenshot.h"

bool Screenshot::Screen(HWND hwnd, cv::Mat* imagePtr)
{
	// 变量初始化
	RECT rect;
	BITMAP info{};

	// 异常标志位
	bool Flag = TRUE;

	// 获取句柄位置
	if (GetWindowRect(hwnd, &rect) == FALSE)
		Flag = FALSE;
	if (rect.left < 0)
		rect.left = 0;
	if (rect.top < 0)
		rect.top = 0;
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 获取句柄DC设备上下文
	HDC hdc = GetDC(hwnd);

	// 创建指定设备上下文兼容的设备上下文
	HDC Create_hdc = CreateCompatibleDC(hdc);

	// 创建指定设备上下文相同大小的位图
	HBITMAP bit = CreateCompatibleBitmap(hdc, width, height);

	if (hdc == NULL || Create_hdc == NULL || bit == NULL)Flag = FALSE;

	// 将HDC设备上下文句柄传递给bit位图句柄
	SelectObject(Create_hdc, bit);

	// 将原hdc图像数据部分复制给Create_hdc图像数据部分
	if (BitBlt(Create_hdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY) == FALSE)Flag = FALSE;

	// 获取到bit位图的信息，并存储在info当中
	if (GetObjectA(bit, sizeof(BITMAP), &info) == 0)Flag = FALSE;

	// 根据bit位图信息确认图像通道数
	int channels = info.bmBitsPixel == 1 ? 1 : info.bmBitsPixel / 8;
	// 创建cv::Mat，由info结构体数据中决定
	cv::Mat image(cv::Size(info.bmWidth, info.bmHeight), CV_MAKETYPE(CV_8U, channels));

	// 将bit位图数据复制到image数据当中
	if (GetBitmapBits(bit, info.bmHeight * info.bmWidth * channels, image.data) == 0)Flag = FALSE;

	cv::cvtColor(image, image, cv::COLOR_RGBA2RGB);

	// 释放资源
	ReleaseDC(hwnd, hdc);
	DeleteDC(Create_hdc);
	DeleteObject(bit);

	if (Flag)
	{ 
		*imagePtr = image.clone();
		return TRUE;
	}
	return FALSE;
}

Ment Screenshot::GetFullScreen(HWND hwnd, cv::Mat& buffer)
{
	return ok;
}

Ment Screenshot::GetWindowScreen(HWND hwnd, cv::Mat& buffer)
{
	return ok;
}

int Screenshot::ContinuousScreenshots(int S, char title[MAX_PATH])
{
	int fps = 0;
	double ms = 0;
	cv::Mat img;
	while (1)
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		Screenshot::Screen(FindWindowA(NULL, title),&img);
		fps = fps + 1;
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = endTime - startTime;
		double milliseconds = duration.count();
		ms = ms + milliseconds;
		if (ms + milliseconds > S * 1000)
			break;
	}
	HWND hwnd = FindWindowA(NULL, title);
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	double xiaohao = ms / fps;
	std::cout << "FPS:" << fps << "\t分辨率:"
		<< width << "x" << height << "\t平均帧消耗:" << xiaohao << "\t目标标题:" << title << std::endl;
	DestroyWindow(hwnd);
	return 0;
}

/*
 * 模板匹配
 * @param img 截图的CV::Mat对象指针
 * @param temp 模板的CV::Mat对象指针
 * @param X 坐标系X轴
 * @param Y 坐标系Y轴
 * @return bool 是否识别到
 */
bool Identify::matching(const cv::Mat& img, const cv::Mat& temp, int& X, int& Y)
{
	cv::Mat result;
	cv::matchTemplate(img, temp, result, cv::TM_CCOEFF_NORMED);
	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	cv::rectangle(img, maxLoc, cv::Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), cv::Scalar(0, 255, 0), 2);
	X = maxLoc.x;
	Y = maxLoc.y;
	if (maxVal > 0.80)
	{
		std::cout << "匹配量：" << maxVal << "\t坐标系：" << X << "," << Y << std::endl;
		return true;
	}
	std::cout << "匹配量：" << maxVal << "\t坐标系：" << X << "," << Y << std::endl;
	return false;
}
