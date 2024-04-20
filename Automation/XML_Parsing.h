#ifndef XML_PARSING_H
#define XML_PARSING_H

#include <string>
#include <Windows.h>
#include <vector>
#include <opencv2/opencv.hpp>

#include "tinyxml2.h"
#include "Enumeration.h"

using namespace tinyxml2;

struct Task_odd {
	const char* Name;
	const char* Type;
	const char* Path;
	const char* Text;
	const char* Act;
	cv::Mat Temp;
};

struct Task {
	const char* Tag;
	const char* Title;
	const char* Note;
};

class XML
{
private:
	tinyxml2::XMLDocument XmlDoc;
	XMLElement* Root;
	XMLElement* Task;
	int TaskLength;
public:
	XML();
	~XML();
	void GetTaskType();
	void ChoiceTask(const char* Tag);
	int GetTaskLength();
	std::vector<Task_odd> GetTaskData();
};

#endif