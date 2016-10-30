#pragma once
#include <iostream>
#include <vector>
#include "ProgramBlocker.h"
#include "TextField.h"
#include "Button.h"

class BlockManager
{
public:
	BlockManager();
	friend std::ostream& operator << (std::ostream& os, BlockManager& bm)
	{
		os << bm.blockers.size() << std::endl;
		for (int i = 0; i < bm.blockers.size(); i++)
		{
			os << *bm.blockers[i];
		}
		return os;
	}
	friend std::istream& operator >> (std::istream& is, BlockManager& bm)
	{
		int size;
		is >> size;
		for (int i = 0; i < size; i++)
		{
			ProgramBlocker* pb = new ProgramBlocker();
			is >> *pb;
			bm.blockers.push_back(pb);
		}
		return is;
	}
	void rebind();
	void update();
	void draw();
	~BlockManager();
private:
	bool nameClear(std::string);
	TextField pbName;
	ScreenText exactText;
	ScreenText mediaText;
	Button exact;
	Button media;
	std::vector<ProgramBlocker*> blockers;
};

