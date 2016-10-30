#pragma once
#include <SDL.h>
#include <string>
#include "KeyManager.h"
#include "ScreenText.h"

class TextField
{
public:
	TextField(double x, double y, double w, double h);
	TextField(std::string* initText, double x, double y, double w, double h);
	static TextField* activeField;
	std::string inputText;
	void setAsActiveField()
	{
		activeField = this;
	}
	void removeAsActiveField()
	{
		if (activeField == this)
		{
			activeField = NULL;
		}
	}
	bool isSelected()
	{
		return (activeField == this);
	}
	void setColor(int r2, int g2, int b2)
	{
		r = r2;
		g = g2;
		b = b2;
	}
	void update(SDL_Event* e);
	void update2(SDL_Event* e);
	std::string textInField();
	void draw();
	void draw(double r, double g, double b, double a);
	void drawOverlay();
	void drawOverlay(double r, double g, double b, double a);
	~TextField();
private:
	ScreenText* screenText;
	double fontSize;
	double x;
	double y;
	double w;
	double h;
	int r;
	int g;
	int b;
	void mouseSetCursorPos();
	void setEndPos();
	void changeText(int change);
	void moveCursor(int change);
	void setCursor(int pos);
	void updateCursorX();
	double cursorX = 4;
	int endPos = 0;
	int cursorPos = 0;
	int wordPos = 0;
};
