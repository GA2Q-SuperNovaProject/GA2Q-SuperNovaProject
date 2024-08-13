//Debug.h

#pragma once
#include <string>

class Debug
{
public:
	static void Trace(int _content);
	static void Trace(double _content);
	static void Trace(std::string _desc);
	static void Trace(std::string _desc, int _content);
	static void Trace(std::string _desc, double _content);
	static void Trace(std::string _desc, int _content, int _content2);
	static void Trace(std::string _desc, double _content, double _content2);

	static bool GetCanDebug() { return canDebug; }
	static void SetCanDebug(bool val) { canDebug = val; }

private:
	static bool canDebug;
};