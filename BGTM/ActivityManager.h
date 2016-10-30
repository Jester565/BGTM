#pragma once
#include <Windows.h>
#include <string>

class ActivityManager
{
public:
	ActivityManager();
	static void update();
	static bool isActive();
	static bool isActive(std::string name, bool exact, bool media);
private:
	static std::string activeWindowName;
	static double lastActivityTime;
	~ActivityManager();
};

