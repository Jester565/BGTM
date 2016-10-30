#pragma once
#include <string>
#include "ScreenText.h"
class CalenderEvent
{
public:
	private:
		std::string eventStr;
		std::string* boundStr;
		std::string eventStr2;
		ScreenText eventText;
		ScreenText eventText2;
	public:
		CalenderEvent();

		std::string getEventStr()
		{
			return eventStr;
		}

		void releaseString();

		void bindString(std::string* str);

		void setEventName(std::string name);

		void draw(int x, int y, int w, int h);

		friend std::ostream& operator<<(std::ostream& os, const CalenderEvent& ce)
		{
			if (ce.eventStr2.size() > 0)
				os << 2 << std::endl;
			else
				os << 1 << std::endl;
			os << ce.eventStr << std::endl;
			if (ce.eventStr2.size() > 0)
				os << ce.eventStr2;
			return os;
		}

		friend std::istream& operator>>(std::istream& is, CalenderEvent& ce)
		{
			int sNum;
			is >> sNum;
			is >> ce.eventStr;
			if (sNum > 1)
				is >> ce.eventStr2;
			return is;
		}

		~CalenderEvent();
};
