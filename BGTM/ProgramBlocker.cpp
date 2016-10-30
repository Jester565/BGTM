#include "ProgramBlocker.h"
#include "BGTM.h"
#include "CalenderEvent.h"
#include "ActivityManager.h"
#include <boost/algorithm/string.hpp>

ProgramBlocker::ProgramBlocker()
{

}

ProgramBlocker::ProgramBlocker(std::string name, bool exact, bool media)
{
	set(name, exact, media);
	std::cout << "event made" << std::endl;
}

void ProgramBlocker::set()
{
	cEvent = BGTM::getCalender()->addEvent(name);
	timeStr = timeToString(timeSpent);
	cEvent->bindString(&timeStr);
}

void ProgramBlocker::set(std::string name_, bool exact_, bool media_)
{
	name = boost::algorithm::to_lower_copy(name_);
	exact = exact_;
	media = media_;
	cEvent = BGTM::getCalender()->addEvent(name);
	timeStr = timeToString(timeSpent);
	cEvent->bindString(&timeStr);
}

void ProgramBlocker::update()
{
	if (ActivityManager::isActive(name, exact, media))
	{
		timeSpent += BGTM::timePassed / 1000.0;
		timeStr = timeToString((int)timeSpent);
	}
}

void ProgramBlocker::rebind()
{
	timeSpent = 0;
	cEvent->releaseString();
	set();
}

std::string ProgramBlocker::timeToString(int time)
{
	int hour = time / 3600;
	int min = (time % 3600) / 60;
	int sec = (time % 3600) % 60;
	std::string hourS = std::to_string(hour);
	std::string minS = std::to_string(min);
	std::string secS = std::to_string(sec);
	if (minS.length() < 2)
	{
		minS = "0" + minS;
	}
	if (secS.length() < 2)
	{
		secS = "0" + secS;
	}
	return hourS + ":" + minS + ":" + secS;
}

ProgramBlocker::~ProgramBlocker()
{
}
