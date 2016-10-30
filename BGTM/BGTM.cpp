#include "BGTM.h"
#include "ActivityManager.h"
#include "AudioDetector.h"
#include <iostream>
#include <fstream>

BGTM::BGTM()
	:RenderCore('b')
{
	saveTmr = 0;
}

CalenderStorage BGTM::calender;

CalenderStorage* BGTM::getCalender()
{
	return &calender;
}

bool BGTM::init()
{
	RenderCore::init();
	std::ifstream myFile;
	bool fileFound = false;
	myFile.open("calender.txt");
	if (myFile.good())
	{
		myFile >> calender;
		calender.updateYears();
		myFile >> bm;
		fileFound = true;
	}
	myFile.close();
	if (!fileFound)
		calender.updateYears();
	AudioDetector::initializeAudioAnalyzer();
	return true;
}

void BGTM::draw()
{
	ActivityManager::update();
	calender.draw(); 
	bm.update();
	bm.draw();
	if (calender.dayChanged())
		bm.rebind();
	saveTmr += timePassed;
	if (saveTmr > 30000 && ActivityManager::isActive())
	{
		save();
	}
}

void BGTM::save()
{
	std::cout << "saved" << std::endl;
	std::ofstream myFile;
	myFile.open("calender.txt");
	myFile << calender;
	myFile << bm;
	myFile.close();
	saveTmr = 0;
}

BGTM::~BGTM()
{
}
