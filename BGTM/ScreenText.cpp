#include "ScreenText.h"
#include "RenderCore.h"
#include <iostream>

ScreenText::ScreenText()
{
	fontImage = NULL;
	lastFontSize = 0;
	lastRestrictWidth = 0;
}

std::map <int, TTF_Font*> ScreenText::fontSizes;

const char* ScreenText::fontPath = "SlimJim.ttf";

int ScreenText::getTextLength(std::string text, int fontSize)
{
	if (text.length() > 0)
	{
		SDL_Color color{ 0, 0, 0 };
		SDL_Surface* textSurface = TTF_RenderText_Solid(getFont(fontSize), text.c_str(), color);
		if (textSurface == NULL)
		{
			printf("Unable to create font! SDL_TTF Error: ", TTF_GetError);
			return 0;
		}
		int width = textSurface->w;
		SDL_FreeSurface(textSurface);
		return width;
	}
	return 0;
}

void ScreenText::drawText(std::string text, int fontSize, double x, double y, double r, double g, double b, double restrictW)
{
	if (text != lastText || lastRestrictWidth != (int)restrictW || fontSize != lastFontSize)
	{
		while (getTextLength(text, fontSize) > restrictW && text.length() > 0)
		{
			text = text.substr(0, text.length() - 1);
		}
		cutText = text;
	}
	drawText(cutText, fontSize, x, y, r, g, b);
}
void ScreenText::drawText(std::string text, int fontSize, double x, double y, double r, double g, double b)
{
	if (fontSize != lastFontSize || text != lastText || r != lastColor.r || g != lastColor.g || b != lastColor.b)
	{
		lastColor.r = r;
		lastColor.g = g;
		lastColor.b = b;
		SDL_Surface* textSurface = TTF_RenderText_Solid(getFont(fontSize), text.c_str(), lastColor);
		if (textSurface == NULL)
		{
			printf("Unable to create font! SDL_TTF Error: ", TTF_GetError);
			return;
		}
		if (fontImage == NULL)
		{
			fontImage = new RenderIMG(textSurface);
		}
		else
		{
			fontImage->resetImage(textSurface);
		}
		textWidth = textSurface->w;
		lastFontSize = fontSize;
		lastText = text;
	}
	fontImage->draw(x, y);
}

TTF_Font* ScreenText::getFont(int size)
{
	TTF_Font* font = NULL;
	if (fontSizes.find(size) == fontSizes.end())
	{
		font = TTF_OpenFont(fontPath, size);
		if (font == NULL)
		{
			return NULL;
		}
		fontSizes.insert(std::pair<int, TTF_Font*>(size, font));
	}
	else
	{
		font = fontSizes.at(size);
	}
	return font;

}

ScreenText::~ScreenText()
{
	delete fontImage;
	fontImage = NULL;
}