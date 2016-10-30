#include "TextField.h"
#include "Button.h"
#include "MouseManager.h"
#include "ShapeRenderer.h"
#include <iostream>

TextField::TextField(double x2, double y2, double w2, double h2)
{
	x = x2;
	y = y2;
	w = w2;
	h = h2;
	r = 255;
	g = 255;
	b = 255;
	fontSize = (int)(h * .7);
	screenText = new ScreenText();
}

TextField::TextField(std::string* initText, double x2, double y2, double w2, double h2)
{
	x = x2;
	y = y2;
	w = w2;
	h = h2;
	r = 255;
	g = 255;
	b = 255;
	if (initText != NULL)
	{
		inputText = *initText;
	}
	fontSize = (int)(h * .7);
	screenText = new ScreenText();
}

TextField* TextField::activeField = NULL;

void TextField::update(SDL_Event* e)
{
	if (e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
	{
		if (wordPos + cursorPos > 0)
		{
			inputText = inputText.substr(0, wordPos + cursorPos - 1) + inputText.substr(wordPos + cursorPos, inputText.length());
			changeText(-1);
		}
	}
	else if (e->key.keysym.sym == SDLK_LEFT)
	{
		moveCursor(-1);
	}
	else if (e->key.keysym.sym == SDLK_RIGHT)
	{
		moveCursor(1);
	}
	else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
	{
		SDL_SetClipboardText(inputText.c_str());
	}
	else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
	{
		inputText = inputText.substr(0, cursorPos + 1) + SDL_GetClipboardText() + inputText.substr(cursorPos + 1, inputText.size());
	}
}

void TextField::update2(SDL_Event* e)
{
	if (!((e->text.text[0] == 'c' || e->text.text[0] == 'C') && (e->text.text[0] == 'v' || e->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
	{
		inputText = inputText.substr(0, wordPos + cursorPos) + e->text.text + inputText.substr(wordPos + cursorPos, inputText.length());
		changeText(1);
	}
}
void TextField::draw()
{
	if (Button::clickedDrawnButton(x, y, w, h, r, g, b, 1))
	{
		mouseSetCursorPos();
		setAsActiveField();
	}
	else if (MouseManager::left)
	{
		removeAsActiveField();
	}
	if (inputText.size() > 0)
	{
		screenText->drawText(inputText.substr(wordPos, endPos), fontSize, x + 4, y, 0, 0, 0);
	}
	if (activeField == this)
	{
		ShapeRenderer::drawRectangle(cursorX + x + 2, y + (fontSize*.2), 3, fontSize * 1.1, 0, 0, 0, 1);
	}
}

void TextField::drawOverlay()
{
	if (Button::clickedDrawnButton(true, x, y, w, h, r, g, b, 1))
	{
		mouseSetCursorPos();
		setAsActiveField();
	}
	else if (MouseManager::left)
	{
		removeAsActiveField();
	}
	if (inputText.size() > 0)
	{
		screenText->drawText(inputText.substr(wordPos, endPos), fontSize, x + 4, y, 0, 0, 0);
	}
	if (activeField == this)
	{
		ShapeRenderer::drawRectangle(cursorX + x + 2, y + (fontSize*.2), 3, fontSize * 1.1, 0, 0, 0, 1);
	}
}

void TextField::draw(double r, double g, double b, double a)
{
	if (Button::clickedDrawnButton(x, y, w, h, r, g, b, a))
	{
		mouseSetCursorPos();
		setAsActiveField();
	}
	else if (MouseManager::leftClicked)
	{
		removeAsActiveField();
	}
	if (inputText.size() > 0)
	{
		screenText->drawText(inputText.substr(wordPos, endPos), fontSize, x + 4, y, 0, 0, 0);
	}
	if (activeField == this)
	{
		ShapeRenderer::drawRectangle(cursorX + x + 2, y + (fontSize*.2), 3, fontSize * 1.1, 0, 0, 0, 1);
	}
}

void TextField::drawOverlay(double r, double g, double b, double a)
{
	if (Button::clickedDrawnButton(true, x, y, w, h, r, g, b, a))
	{
		mouseSetCursorPos();
		setAsActiveField();
	}
	else if (MouseManager::left)
	{
		removeAsActiveField();
	}
	if (inputText.size() > 0)
	{
		screenText->drawText(inputText.substr(wordPos, endPos), fontSize, x + 4, y, 0, 0, 0);
	}
	if (activeField == this)
	{
		ShapeRenderer::drawRectangle(cursorX + x + 2, y + (fontSize*.2), 3, fontSize * 1.1, 0, 0, 0, 1);
	}
}

void TextField::mouseSetCursorPos()
{
	bool maxedOut = false;
	double shownLength = 0;
	int cursorPosLocal = 0;
	int modifiedMouseX = MouseManager::x - (x + (h*.2));
	if (modifiedMouseX < 0)
	{
		setCursor(0);
	}
	else
	{
		while (shownLength < w && shownLength < modifiedMouseX && cursorPosLocal <= endPos)
		{
			shownLength = ScreenText::getTextLength(inputText.substr(wordPos, cursorPosLocal), fontSize);
			cursorPosLocal++;
		}
		cursorPosLocal--;
		setCursor(cursorPosLocal);
	}
}

std::string TextField::textInField()
{
	return inputText;
}

void TextField::moveCursor(int change)
{
	if (change < 0)
	{
		for (int i = 0; i < abs(change); i++)
		{
			if (cursorPos > 0)
			{
				cursorPos--;
			}
			else
			{
				if (wordPos > 0)
				{
					wordPos--;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < change; i++)
		{
			if (wordPos + cursorPos < inputText.length() && ScreenText::getTextLength((inputText.substr(wordPos, cursorPos + 2)), fontSize) < w - 25)
			{
				cursorPos++;
			}
			else
			{
				if (wordPos + cursorPos < inputText.length())
				{
					wordPos++;
				}
			}
			if (ScreenText::getTextLength(inputText.substr(wordPos, cursorPos + 1), fontSize) > w - 15)
			{
				cursorPos--;
				wordPos++;
			}
		}
	}
	updateCursorX();
	setEndPos();
}

void TextField::setCursor(int pos)
{
	if (cursorPos < 0)
	{
		cursorPos = 0;
	}
	if (wordPos + pos <= inputText.length())
	{
		cursorPos = pos;
	}
	else
	{
		cursorPos = inputText.length() - wordPos;
	}
	updateCursorX();
}
void TextField::changeText(int change)
{
	if (change < 0)
	{
		for (int i = 0; i < abs(change); i++)
		{
			if (wordPos == 0)
			{
				if (cursorPos > 0)
				{
					cursorPos--;
				}
			}
			else
			{
				wordPos--;
			}
		}
	}
	else
	{
		for (int i = 0; i < change; i++)
		{
			if (ScreenText::getTextLength(inputText.substr(wordPos, cursorPos + 1), fontSize) < w - 25)
			{
				cursorPos++;
			}
			else
			{
				wordPos++;
			}
			if (ScreenText::getTextLength(inputText.substr(wordPos, cursorPos + 1), fontSize) > w - 15)
			{
				cursorPos--;
				wordPos++;
			}
		}
	}
	setEndPos();
	updateCursorX();
}

void TextField::updateCursorX()
{
	std::string subWord = inputText.substr(wordPos, cursorPos);
	cursorX = ScreenText::getTextLength(subWord, fontSize);
}

void TextField::setEndPos()
{
	int i = 0;
	while (i < inputText.length() && ScreenText::getTextLength(inputText.substr(wordPos, i), fontSize) <= w - 15)
	{
		i++;
	}
	endPos = i;
}

TextField::~TextField()
{
	removeAsActiveField();
	delete screenText;
}