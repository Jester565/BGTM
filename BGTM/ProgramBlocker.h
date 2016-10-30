#pragma once
#include <string>
#include "CalenderStorage.h"

class ProgramBlocker
{
public:
	ProgramBlocker();
	ProgramBlocker(std::string name, bool exact, bool media);
	void set(std::string name, bool exact, bool media);
	void set();
	void update();
	void rebind();
	const std::string& getName()
	{
		return name;
	}
	friend std::ostream& operator << (std::ostream& os, ProgramBlocker& pb)
	{
		os << pb.name << std::endl;
		os << pb.timeSpent << std::endl;
		os << pb.exact << std::endl;
		os << pb.media << std::endl;
		return os;
	}
	friend std::istream& operator >> (std::istream& is, ProgramBlocker& pb)
	{
		is >> pb.name >> pb.timeSpent >> pb.exact >> pb.media;
		pb.set();
		return is;
	}
	~ProgramBlocker();
private:
	std::string name;
	std::string timeStr;
	std::string timeToString(int time);
	double timeSpent = 0;
	bool exact = false;
	bool media = false;
	CalenderEvent* cEvent;
};
