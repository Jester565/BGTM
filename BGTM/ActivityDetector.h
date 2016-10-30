#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

static const unsigned int idle_milliseconds = 60 * 10 * 1000;

static const unsigned int interval = 60 * 60 * 1000;
class ActivityDetector
{
public:
	ActivityDetector();
	static int getInactiveMiliSeconds();
	~ActivityDetector();
private:
	static DWORD lastTickCount;
	static DWORD counter;
};