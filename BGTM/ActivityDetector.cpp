#include "ActivityDetector.h"
#include "BGTM.h"

ActivityDetector::ActivityDetector()
{
}

DWORD ActivityDetector::counter = 0;

DWORD ActivityDetector::lastTickCount = 0;

int ActivityDetector::getInactiveMiliSeconds()
{
	LASTINPUTINFO info;
	info.cbSize = sizeof(info);
	GetLastInputInfo(&info);
	if (info.dwTime != lastTickCount)
	{
		counter = 0;
		lastTickCount = info.dwTime;
	}
	counter += BGTM::timePassed;
	return counter;
}

ActivityDetector::~ActivityDetector()
{
}
