#ifndef BUSINESS_H
#define BUSINESS_H

#include <Windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

#include "Screenshot.h"
#include "XML_Parsing.h"
#include "Win32API.h"
#include "Enumeration.h"

/* ͼ����󻺳��� */
class Buffer
{
private:
	std::mutex mtx;
	cv::Mat buffer_A;
	bool lock = false;
public:
	Buffer();
	~Buffer();
	cv::Mat buffer_B;
	void write(HWND hwnd);
	void read();
};

/* ������� */
class task
{
private:
	const char* Tag;
	std::vector<Task_odd> task;
	int step = 0;
	int length = 0;
public:
	void task_init(const char* tag);
	void task_Clear();
	friend class business;
};

/* ҵ����� */
class business
{
private:
	HWND hwnd;
	Buffer buffer;
	cv::Mat Image;
	bool Flag = false;	// ������ɱ�־λ
public:
	business(HWND Handle);
	~business();
	void ScreenThread();
	void service(task& obj);
	bool BusinessCallback(Task_odd& Odd);
};

#endif