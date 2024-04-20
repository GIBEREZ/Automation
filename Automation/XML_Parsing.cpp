#include "XML_Parsing.h"


XML::XML()
{
    OutputDebugStringA("读取XML文件\n");
	this->XmlDoc.LoadFile("DB.xml");
    OutputDebugStringA("读取分支\n");
	this->Root = XmlDoc.RootElement();
}

XML::~XML()
{
    this->XmlDoc.Clear();
}

void XML::GetTaskType()
{
    this->Root->FirstChildElement();
}

void XML::ChoiceTask(const char* Tag)
{
	this->Task = Root->FirstChildElement(Tag);
}

int XML::GetTaskLength()
{
    OutputDebugStringA("获取单条任务列表步骤长度\n");
    int Count = 0;
    XMLElement* trunkElement = this->Task->FirstChildElement("trunk");
    while (trunkElement) {
        Count++;
        trunkElement = trunkElement->NextSiblingElement("trunk");
    }
    this->TaskLength = Count;
    return Count;
}

std::vector<Task_odd> XML::GetTaskData()
{
    OutputDebugStringA("解析任务列表中的数据\n");
    std::vector<Task_odd> task;
    for (tinyxml2::XMLElement* trunk = this->Task->FirstChildElement("trunk"); trunk; trunk = trunk->NextSiblingElement("trunk")) 
    {
        Task_odd Odd;
        Odd.Name = trunk->Attribute("name");
        Odd.Type = trunk->Attribute("type");
        Odd.Path = trunk->Attribute("path");
        Odd.Text = trunk->Attribute("text");
        Odd.Act = trunk->Attribute("act");

        std::cout << "Name: " << Odd.Name << std::endl;
        std::cout << "Type: " << Odd.Type << std::endl;
        if (strcmp(Odd.Type, "图像识别") == 0)
        {
            Odd.Temp = cv::imread(Odd.Path);
            if (!Odd.Temp.empty())
            {
                std::cout << "Temp: 图像已加载" << std::endl;
            }
            else
            {
                std::cout << "Temp: 图像加载失败" << std::endl;
            }
        }
        std::cout << "Path: " << Odd.Path << std::endl;
        std::cout << "Text: " << Odd.Text << std::endl;
        std::cout << "Act: " << Odd.Act << std::endl;
        std::cout << std::endl;

        task.push_back(Odd);
    }
    return task;
}
