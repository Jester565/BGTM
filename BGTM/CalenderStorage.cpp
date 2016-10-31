#include "CalenderStorage.h"

Date::Date()
{

}

void Date::setToCurrentDate()
{
	namespace pt = boost::posix_time;
	pt::to_iso_string(pt::second_clock::local_time());
	namespace pt = boost::posix_time;
	set(pt::second_clock::local_time());
}

void Date::set(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

void Date::set(boost::posix_time::ptime now)
{
	month = static_cast<int>(now.date().month()) - 1;
	day = now.date().day() - 1;
	year = now.date().year();
}

Day::Day(Date* today, int year, int month, int dayOfMonth_, int dayOfWeek_)
{
	this->today = today;
	this->year = year;
	this->month = month;
	dayOfMonth = dayOfMonth_;
	dayOfWeek = dayOfWeek_;
	dayOfMonthString = std::to_string(dayOfMonth + 1);
}

void Day::draw(int x, int y, int w, int h)
{
	if (year == today->year && month == today->month && dayOfMonth == today->day)
	{
		ShapeRenderer::drawRectangle(x, y, w, h, 255, 0, 0, 255);
	}
	else
	{
		ShapeRenderer::drawRectangle(x, y, w, h, 0, 0, 255, 255);
	}
	dayOfMonthText.drawText(dayOfMonthString, h*.2, x + 4, y + h * .8, 0, 255, 0);
	for (int i = 0; i < cEvents.size(); i++)
	{
		cEvents[i]->draw(x + 3, y + h - (i + 1.8) * h / 5.0, w - 4, h / 5.0);
		if (h - (i + 1.8) * h / 5.0 < 0)
		{
			return;
		}
	}
}

Week::Week(Date* today, int year, int month, int startDate, int startDay, int endDay, std::istream* iStream)
{
	if (endDay > 7)
	{
		endDay = 7;
	}
	for (int i = startDay; i < endDay; i++)
	{
		Day* nDay = new Day(today, year, month, i + startDate - startDay, i);
		if (iStream != nullptr)
		{
			(*iStream) >> *nDay;
		}
		days.push_back(nDay);
	}
	this->startDay = startDay;
	this->endDay = endDay;
}

void Week::draw(int x, int y, int w, int h)
{
	ShapeRenderer::drawRectangle(x, y, w, h, 0, 0, 0, 255);
	for (int i = 0; i < days.size(); i++)
	{
		days[i]->draw(x + 4 + (startDay + i) * (w / 7.0), y, w / 7.0 - 4, h);
	}
}
void Week::save(std::ostream& os)
{
	for (int i = 0; i < days.size(); i++)
	{
		os << *days[i];
	}
}

Day* Week::getDay(int day)
{
	for (int i = 0; i < days.size(); i++)
	{
		if (days[i]->dayOfMonth == day)
		{
			return days[i];
		}
	}
	return nullptr;
}

Month::Month(Date* today, int yearNum, int monthNum, std::istream* iStream)
{
	this->today = today;
	if (monthNum % 2 == 0)
	{
		amountOfDays = 30;
	}
	else
	{
		amountOfDays = 31;
	}
	if (monthNum == 1)
	{
		if (yearNum % 4 == 0)
		{
			amountOfDays = 29;
		}
		else
		{
			amountOfDays = 28;
		}
	}
	startingDay = dayOfWeek(1, monthNum + 1, yearNum);
	int localStartDay = startingDay;
	int dayAmount = amountOfDays + startingDay;
	while (dayAmount > 0)
	{
		weeks.push_back(new Week(today, yearNum, monthNum, amountOfDays - (dayAmount - localStartDay), localStartDay, dayAmount, iStream));
		localStartDay = 0;
		dayAmount -= 7;
	}
	name = getMonthName(monthNum);
}

int Month::dayOfWeek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
void Month::draw(int x, int y, int w, int h)
{
	ShapeRenderer::drawRectangle(x, y, w, h, 40, 40, 40, 255);
	for (int i = 0; i < weeks.size(); i++)
	{
		weeks[i]->draw(x, y - (i + 1) * (h / weeks.size()) + h, w, h / weeks.size());
	}
	monthName.drawText(name, 30, x, y + h + 5, 30, 30, 30);
}
std::string Month::getMonthName(int monthNum)
{
	const std::string months[12] = { "January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return months[monthNum];
}
void Month::save(std::ostream& os)
{
	for (int i = 0; i < weeks.size(); i++)
	{
		weeks[i]->save(os);
	}
}
Day* Month::getDay(int day)
{
	for (int i = 0; i < weeks.size(); i++)
	{
		if (weeks[i]->getDay(day) != nullptr)
		{
			return weeks[i]->getDay(day);
		}
	}
	return nullptr;
}

Year::Year(Date* today, int yearNumber, std::istream* iStream)
{
	activeMonth = today->month;
	yearNum = yearNumber;
	for (int i = 0; i < 12; i++)
	{
		months.push_back(new Month(today, yearNumber, i, iStream));
	}
}

void Year::draw(int x, int y, int w, int h)
{
	months[activeMonth]->draw(x, y, w, h);
	if (activeMonth > 0 && left.timeButtonClicked(x - 50, y + h / 2, 40, 20, 0, 255, 0, 255))
	{
		activeMonth--;
	}
	if (activeMonth < 11 && right.timeButtonClicked(x + 10 + w, y + h / 2, 40, 20, 0, 255, 0, 255))
	{
		activeMonth++;
	}
}

void Year::save(std::ostream& os)
{
	for (int i = 0; i < months.size(); i++)
	{
		months[i]->save(os);
	}
}

Day* Year::getDay(int month, int day)
{
	return months[month]->getDay(day);
}

CalenderStorage::CalenderStorage()
{
	today = new Date();
	today->setToCurrentDate();
	lastYear = today->year - 1;
	lastUpdateDay = today->day;
}

void CalenderStorage::draw()
{
	years[0]->draw(50, 50, 1820, 920);
}

Day* CalenderStorage::getDay(int year, int month, int day)
{
	for (int i = 0; i < years.size(); i++)
	{
		if (years[i]->yearNum == year)
		{
			return years[i]->getDay(month, day);
		}
	}
	return nullptr;
}

bool CalenderStorage::dayChanged()
{
	today->setToCurrentDate();
	if (lastUpdateDay != today->day)
	{
		lastUpdateDay = today->day;
		return true;
	}
	return false;
}

CalenderEvent* CalenderStorage::addEvent(std::string eventName)
{
	Day* day = getDay(today->year, today->month, today->day);
	for (int i = 0; i < day->cEvents.size(); i++)
	{
		if (eventName == day->cEvents[i]->getEventStr())
		{
			return day->cEvents[i];
		}
	}
	CalenderEvent* cEvent = new CalenderEvent();
	std::cout << "Set new event " << eventName << std::endl;
	cEvent->setEventName(eventName);
	day->cEvents.push_back(cEvent);
	return cEvent;
}

void CalenderStorage::updateYears()
{
	while (lastYear < today->year)
	{
		lastYear++;
		years.push_back(new Year(today, lastYear));
	}
}

CalenderStorage::~CalenderStorage()
{
}
