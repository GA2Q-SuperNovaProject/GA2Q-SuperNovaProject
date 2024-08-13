//Debug.cpp

//#include "pch.h" //주석처리 했을 때 컴파일러 에러가 없다면 빼도 됨 
#include "Debug.h"
#include <sstream>
#include <windows.h>
#include <string>
#include <debugapi.h>

//디버깅 여부를 키는 옵션. False면 OutputDebugString이 나오지 않는다.
bool Debug::canDebug = false;

void Debug::Trace(std::string _desc)
{
	if (canDebug)
	{
		std::wstring wsConverted = L"";
		wsConverted.assign(_desc.begin(), _desc.end());
		OutputDebugString(wsConverted.c_str());
	}
}

void Debug::Trace(double _content)
{
	if (canDebug)
	{
		std::wstring tmpConverted = std::to_wstring(_content);
		OutputDebugString(tmpConverted.c_str());
	}
}

void Debug::Trace(int _content)
{
	if (canDebug)
	{
		std::wstring tmpConverted = std::to_wstring(_content);
		OutputDebugString(tmpConverted.c_str());
	}
}

void Debug::Trace(std::string _desc, int _content)
{
	std::string contentString = std::to_string(_content);
	_desc = _desc + ": " + contentString;
	std::wstring wsConverted = L"";
	wsConverted.assign(_desc.begin(), _desc.end());
	OutputDebugString(wsConverted.c_str());
}

void Debug::Trace(std::string _desc, double _content)
{
	std::string contentString = std::to_string(_content);
	_desc = _desc + ": " + contentString;
	std::wstring wsConverted = L"";
	wsConverted.assign(_desc.begin(), _desc.end());
	OutputDebugString(wsConverted.c_str());
}

void Debug::Trace(std::string _desc, int _content, int _content2)
{
	std::string contentString = std::to_string(_content);
	std::string contentString2 = std::to_string(_content2);
	_desc = _desc + ": (" + contentString + ", " + contentString2 + ")";
	std::wstring wsConverted = L"";
	wsConverted.assign(_desc.begin(), _desc.end());
	OutputDebugString(wsConverted.c_str());
}

void Debug::Trace(std::string _desc, double _content, double _content2)
{
	std::string contentString = std::to_string(_content);
	std::string contentString2 = std::to_string(_content2);
	_desc = _desc + ": (" + contentString + ", " + contentString2 + ")";
	std::wstring wsConverted = L"";
	wsConverted.assign(_desc.begin(), _desc.end());
	OutputDebugString(wsConverted.c_str());
}