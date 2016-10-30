#pragma once
#include <vector>
#include <list>
#include <map>
#include <ctime>
#include <boost/date_time.hpp>
#include <iostream>
#include "ScreenText.h"
#include "ShapeRenderer.h"
#include "Button.h"
#include "CalenderEvent.h"

struct Date
{
	Date();

	void setToCurrentDate();

	void set(int year, int month, int day);

	void set(boost::posix_time::ptime now);

	friend std::ostream& operator <<(std::ostream& os, Date& date)
	{
		os << date.year << std::endl;
		os << date.month << std::endl;
		os << date.day << std::endl;
		return os;
	}
	friend std::istream& operator >> (std::istream& is, Date& date)
	{
		is >> date.year >> date.month >> date.day;
		return is;
	}
	bool equals(Date* d)
	{
		return (day == d->day && month == d->month && year == d->year);
	}
	int year;
	int month;
	int day;
};

struct Day
{
	Date* today;
	std::vector <CalenderEvent*> cEvents;
	ScreenText dayOfMonthText;
	std::string dayOfMonthString;
	int dayOfMonth, dayOfWeek, year, month;
	Day(Date* today, int year, int month, int dayOfMonth_, int dayOfWeek_);

	void draw(int x, int y, int w, int h);

	friend std::ostream& operator<<(std::ostream& os, const Day& s)
	{
		os << s.cEvents.size() << std::endl;
		for (int i = 0; i < s.cEvents.size(); i++)
		{
			os << (*(s.cEvents[i])) << std::endl;
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Day& s)
	{
		int listSize;
		is >> listSize;
		for (int i = 0; i < listSize; i++)
		{
			CalenderEvent ce;
			is >> ce;
			CalenderEvent* cPtr = new CalenderEvent(ce);
			s.cEvents.push_back(cPtr);
		}
		std::cout << "Day Loaded" << std::endl;
		return is;
	}

};

struct Week
{
	Date* today;
	int startDay, endDay;
	std::vector<Day*> days;

	Week(Date* today, int year, int month, int startDate, int startDay, int endDay, std::istream* iStream = nullptr);

	void draw(int x, int y, int w, int h);

	void save(std::ostream& os);

	Day* getDay(int day);

};

struct Month
{
	int monthNumber;
	int startingDay;
	int amountOfDays;
	Date* today;
	ScreenText monthName;
	std::string name;
	std::vector<Week*> weeks;

	Month(Date* today, int yearNum, int monthNum, std::istream* iStream = nullptr);

	int dayOfWeek(int d, int m, int y);

	void draw(int x, int y, int w, int h);

	std::string getMonthName(int monthNum);

	void save(std::ostream& os);

	Day* getDay(int day);

};
struct Year
{
	std::vector<Month*> months;
	int activeMonth = 0;
	int yearNum;
	Button left;
	Button right;

	Year(Date* today, int yearNumber, std::istream* iStream = nullptr);

	void draw(int x, int y, int w, int h);

	void save(std::ostream& os);

	Day* getDay(int month, int day);

};

class CalenderStorage
{
public:
	Date* today;

	bool dayChanged();

	int lastYear;

	CalenderStorage();

	void draw();

	CalenderEvent* addEvent(std::string pbName);

	void updateYears();

	friend std::ostream& operator<<(std::ostream& os, const CalenderStorage& s)
	{
		os << *s.today;
		os << s.years[0]->yearNum << std::endl;
		os << s.years.size() << std::endl;
		for (int i = 0; i < s.years.size(); i++)
		{
			s.years[i]->save(os);
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, CalenderStorage& s)
	{
		Date lastDate;
		is >> lastDate;
		if (!lastDate.equals(s.today))
			s.lastUpdateDay = -2;
		int fYear;
		int yearSize;
		is >> fYear >> yearSize;
		for (int i = 0; i < yearSize; i++)
		{
			s.years.push_back(new Year(s.today, fYear + i, &is));
		}
		s.lastYear = fYear + yearSize - 1;
		return is;
	}

	~CalenderStorage();

private:

	int yearI;

	int lastUpdateDay;

	std::vector<Year*> years;

	Day* getDay(int year, int month, int day);

};
