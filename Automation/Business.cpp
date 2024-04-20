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
	OutputDebugStringA("��ʼд��ͼ�񻺳�������\n");
	Screenshot::Screen(hwnd, &this->buffer_A);
	mtx.unlock();
}

void Buffer::read()
{ 
	this->lock = true;
	mtx.lock();
	OutputDebugStringA("��ʼ��ȡͼ�񻺳�������\n");
	this->buffer_A.copyTo(this->buffer_B);
	mtx.unlock();
	this->lock = false;
	OutputDebugStringA("��ȡ���\n");
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
	OutputDebugStringA("�߳��ѽ�������ʼ���н�ͼ�߳�\n");
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
	OutputDebugStringA("�߳��ѽ�������ʼ����service�߳�\n");
	while (true)
	{
		Task_odd Odd = obj.task[obj.step];
		if (obj.step < obj.length)
		{
			obj.step++;
			std::cout << "����ִ�е� " << obj.step << " ������" << std::endl;
			this->BusinessCallback(Odd);
		}
		if (obj.step >= obj.length)
		{
			std::cout << "����ִ�����" << std::endl;
			break;
		}
	}
	this->Flag = true;
	OutputDebugStringA("�߳����ͷ�\n");
}

bool business::BusinessCallback(Task_odd& Odd)
{
	OutputDebugStringA("service�̣߳��ѻ�ȡ�����񣬿�ʼ�����������ݣ������¼�ģ����\n");
	if (strcmp(Odd.Type, "ͼ��ʶ��") == 0)
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
				if (strcmp(Odd.Act, "������") == 0)
				{
					WinTool::MouseClick(this->hwnd, X + (Odd.Temp.cols / 2), Y + (Odd.Temp.rows / 2));
				}
				return true;
			}
		}
	}
	return false;
}

