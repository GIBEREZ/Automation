#include "Business.h"

Buffer::Buffer()
{

}

Buffer::~Buffer()
{

}

void Buffer::write(HWND hwnd)
{
	if (lock)
		return;
	mtx.lock();
	OutputDebugStringA("开始写入图像缓冲区对象\n");
	Screenshot::Screen(hwnd, &this->buffer_A);
	mtx.unlock();
}

void Buffer::read()
{ 
	this->lock = true;
	mtx.lock();
	OutputDebugStringA("开始读取图像缓冲区对象\n");
	this->buffer_A.copyTo(this->buffer_B);
	mtx.unlock();
	this->lock = false;
	OutputDebugStringA("读取完毕\n");
}

void task::task_init(const char* tag)
{
	this->Tag = tag;
	XML* xml = new XML();
	xml->ChoiceTask(tag);
	this->task = xml->GetTaskData();
	this->length = xml->GetTaskLength();
}

void task::task_Clear()
{
	
}

business::business(HWND handle)
{
	this->hwnd = handle;
}

business::~business()
{
	DestroyWindow(this->hwnd);
}

void business::ScreenThread()
{
	OutputDebugStringA("线程已建立，开始运行截图线程\n");
	while (true)
	{
		this->buffer.write(this->hwnd);
		if (this->Flag == true)
		{
			break;
		}
	}
}

void business::service(task& obj)
{
	OutputDebugStringA("线程已建立，开始运行service线程\n");
	while (true)
	{
		Task_odd Odd = obj.task[obj.step];
		if (obj.step < obj.length)
		{
			obj.step++;
			std::cout << "正在执行第 " << obj.step << " 个任务" << std::endl;
			this->BusinessCallback(Odd);
		}
		if (obj.step >= obj.length)
		{
			std::cout << "任务执行完成" << std::endl;
			break;
		}
	}
	this->Flag = true;
	OutputDebugStringA("线程已释放\n");
}

bool business::BusinessCallback(Task_odd& Odd)
{
	OutputDebugStringA("service线程，已获取到任务，开始处理任务数据，运行事件模型中\n");
	if (strcmp(Odd.Type, "图像识别") == 0)
	{
		while (true)
		{
			this->buffer.read();
			if (!this->Image.empty())
			{
				break;
			}
			int X = 0;
			int Y = 0;
			if(Identify::matching(this->buffer.buffer_B, Odd.Temp, X, Y) == true)
			{
				std::this_thread::sleep_for(std::chrono::seconds(3));
				if (strcmp(Odd.Act, "鼠标左键") == 0)
				{
					WinTool::MouseClick(this->hwnd, X + (Odd.Temp.cols / 2), Y + (Odd.Temp.rows / 2));
				}
				return true;
			}
		}
	}
	return false;
}

