#include "CalenderEvent.h"


CalenderEvent::CalenderEvent()
	:boundStr(nullptr)
{
}

void CalenderEvent::releaseString()
{
	boundStr = nullptr;
}
void CalenderEvent::bindString(std::string* str)
{
	boundStr = str;
}
void CalenderEvent::setEventName(std::string name)
{
	eventStr = name;
}
void CalenderEvent::draw(int x, int y, int w, int h)
{
	if (boundStr != nullptr)
	{
		eventStr2 = *boundStr;
	}
	if (eventStr2.length() == 0)
	{
		eventText.drawText(eventStr, h, x, y, 255, 255, 1, w - 6);
	}
	else
	{
		eventText.drawText(eventStr, h, x, y, 255, 255, 1, (w / 2.0) - 8);
		eventText2.drawText(eventStr2, h, x + (w / 2.0), y, 255, 255, 0, (w / 2.0) - 4);
	}
}

CalenderEvent::~CalenderEvent()
{
}
