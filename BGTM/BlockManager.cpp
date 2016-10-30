#include "BlockManager.h"

const int addX = 300;
const int addY = 1000;
const int addW = 500;
const int addH = 40;
BlockManager::BlockManager() :
pbName(addX, addY, addW, addH)
{
}

void BlockManager::update()
{
	for (int i = 0; i < blockers.size(); i++)
		blockers[i]->update();
}

void BlockManager::rebind()
{
	for (int i = 0; i < blockers.size(); i++)
		blockers[i]->rebind();
}

void BlockManager::draw()
{
	pbName.draw();
	exact.buttonPressed(addX + addW + exactText.getWidth() + 7, addY + addH/7, addW / 8, addH, 100, 255, 100, 255);
	media.buttonPressed(addX + addW * 1.5 + mediaText.getWidth(), addY + addH/7, addW / 8, addH, 100, 255, 100, 255);
	std::string exactStr = "Contains";
	if (exact.isPressed())
		exactStr = "Exact";
	exactText.drawText(exactStr, addH, addX + addW + 5, addY, 0, 0, 0);
	std::string mediaStr = "Active Based";
	if (media.isPressed())
		mediaStr = "Audio Based";
	mediaText.drawText(mediaStr, addH, addX + addW * 1.5, addY, 0, 0, 0);
	if (Button::clickedDrawnButton(addX + (addW / 2) - addW / 16, addY - addH / 2, addW / 8, addH / 3, 100, 100, 100, 255) && nameClear(pbName.inputText))
		blockers.push_back(new ProgramBlocker(pbName.inputText, exact.isPressed(), media.isPressed()));
}

bool BlockManager::nameClear(std::string name)
{
	if (name.length() < 1)
		return false;
	for (int i = 0; i < blockers.size(); i++)
		if (blockers[i]->getName() == name)
			return false;
	return true;
}

BlockManager::~BlockManager()
{
}
