#pragma once
#include "RenderCore.h"
#include "CalenderStorage.h"
#include "BlockManager.h"
#include "AudioDetector.h"

class BGTM : public RenderCore
{
public:
	BGTM();
	static CalenderStorage* getCalender();
	~BGTM();
protected:
	bool init() override;
	void draw() override;
private:
	static CalenderStorage calender;
	void save();
	BlockManager bm;
	double saveTmr;
};

