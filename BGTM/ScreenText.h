#pragma once
#include "RenderIMG.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

class ScreenText
{
public:
	ScreenText();
	void drawText(std::string text, int fontSize, double x, double y, double r, double g, double b);
	void drawText(std::string text, int fontSize, double x, double y, double r, double g, double b, double restrictW);
	static int getTextLength(std::string text, int width);
	std::string lastText;
	void setAlpha(double alpha);
	int getWidth()
	{
		return textWidth;
	}
	~ScreenText();
private:
	static std::map <int, TTF_Font*> fontSizes;
	static TTF_Font* getFont(int size);
	int lastRestrictWidth;
	int lastFontSize;
	int textWidth;
	int textHeight;
	std::string cutText;
	SDL_Color lastColor;
	RenderIMG* fontImage;
	const static char* fontPath;
};



