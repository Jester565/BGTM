#include "ActivityManager.h"
#include "BGTM.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "ActivityDetector.h"
#include <boost/algorithm/string.hpp>

ActivityManager::ActivityManager()
{
}

std::string ActivityManager::activeWindowName = " ";

double ActivityManager::lastActivityTime = 0;

void ActivityManager::update()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	activeWindowName = boost::algorithm::to_lower_copy((std::string)wnd_title);
	lastActivityTime = ActivityDetector::getInactiveMiliSeconds();
}
bool ActivityManager::isActive(std::string name, bool exact, bool media)
{
	return (lastActivityTime < 60000 || media && AudioDetector::soundPlaying()) && (name == activeWindowName || !exact && activeWindowName.find(name) != -1);
}

bool ActivityManager::isActive()
{
	return lastActivityTime < 60000 || AudioDetector::soundPlaying();
}

ActivityManager::~ActivityManager()
{
}
