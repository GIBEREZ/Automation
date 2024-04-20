#include "Screenshot.h"

bool Screenshot::Screen(HWND hwnd, cv::Mat* imagePtr)
{
	// ������ʼ��
	RECT rect;
	BITMAP info{};

	// �쳣��־λ
	bool Flag = TRUE;

	// ��ȡ���λ��
	if (GetWindowRect(hwnd, &rect) == FALSE)
		Flag = FALSE;
	if (rect.left < 0)
		rect.left = 0;
	if (rect.top < 0)
		rect.top = 0;
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ��ȡ���DC�豸������
	HDC hdc = GetDC(hwnd);

	// ����ָ���豸�����ļ��ݵ��豸������
	HDC Create_hdc = CreateCompatibleDC(hdc);

	// ����ָ���豸��������ͬ��С��λͼ
	HBITMAP bit = CreateCompatibleBitmap(hdc, width, height);

	if (hdc == NULL || Create_hdc == NULL || bit == NULL)Flag = FALSE;

	// ��HDC�豸�����ľ�����ݸ�bitλͼ���
	SelectObject(Create_hdc, bit);

	// ��ԭhdcͼ�����ݲ��ָ��Ƹ�Create_hdcͼ�����ݲ���
	if (BitBlt(Create_hdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY) == FALSE)Flag = FALSE;

	// ��ȡ��bitλͼ����Ϣ�����洢��info����
	if (GetObjectA(bit, sizeof(BITMAP), &info) == 0)Flag = FALSE;

	// ����bitλͼ��Ϣȷ��ͼ��ͨ����
	int channels = info.bmBitsPixel == 1 ? 1 : info.bmBitsPixel / 8;
	// ����cv::Mat����info�ṹ�������о���
	cv::Mat image(cv::Size(info.bmWidth, info.bmHeight), CV_MAKETYPE(CV_8U, channels));

	// ��bitλͼ���ݸ��Ƶ�image���ݵ���
	if (GetBitmapBits(bit, info.bmHeight * info.bmWidth * channels, image.data) == 0)Flag = FALSE;

	cv::cvtColor(image, image, cv::COLOR_RGBA2RGB);

	// �ͷ���Դ
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
	std::cout << "FPS:" << fps << "\t�ֱ���:"
		<< width << "x" << height << "\tƽ��֡����:" << xiaohao << "\tĿ�����:" << title << std::endl;
	DestroyWindow(hwnd);
	return 0;
}

/*
 * ģ��ƥ��
 * @param img ��ͼ��CV::Mat����ָ��
 * @param temp ģ���CV::Mat����ָ��
 * @param X ����ϵX��
 * @param Y ����ϵY��
 * @return bool �Ƿ�ʶ��
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
		std::cout << "ƥ������" << maxVal << "\t����ϵ��" << X << "," << Y << std::endl;
		return true;
	}
	std::cout << "ƥ������" << maxVal << "\t����ϵ��" << X << "," << Y << std::endl;
	return false;
}
