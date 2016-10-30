#include "Button.h"
#include "RenderCore.h"
#include <iostream>

Button::Button()
{
	pressTimer = 0;
}

bool Button::overLayered = false;

void Button::setOverLay(bool mode)
{
	overLayered = mode;
}

bool Button::overButton(double x, double y, double w, double h)
{
	if (!overLayered && MouseManager::x >= x && MouseManager::y >= y && MouseManager::x < x + w && MouseManager::y < y + h)
	{
		return true;
	}
	return false;
}

bool Button::clickedButton(double x, double y, double w, double h)
{
	if (MouseManager::leftClicked && overButton(x, y, w, h))
	{
		return true;
	}
	return false;
}

bool Button::overButton(bool aboveLayer, double x, double y, double w, double h)
{
	if (MouseManager::x >= x && MouseManager::y >= y && MouseManager::x < x + w && MouseManager::y < y + h)
	{
		if (!overLayered || aboveLayer)
		{
			return true;
		}
	}
	return false;
}

bool Button::clickedButton(bool aboveLayer, double x, double y, double w, double h)
{
	if (MouseManager::leftClicked && overButton(aboveLayer, x, y, w, h))
	{
		return true;
	}
	return false;
}

bool Button::clickedDrawnButton(bool aboveLayer, double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (overButton(aboveLayer, x, y, w, h))
	{
		if (MouseManager::leftClicked)
		{
			ShapeRenderer::drawRectangle(x, y, w, h, r / 2, g / 2, b / 2, a);
			return true;
		}
		ShapeRenderer::drawRectangle(x, y, w, h, r / 1.6, g / 1.6, b / 1.6, a);
		return false;
	}
	ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
	return false;
}

bool Button::clickedButton(int key, double x, double y, double w, double h)
{
	if (mouseKeyPressed(key) && overButton(x, y, w, h))
	{
		return true;
	}
	return false;
}

bool Button::clickedDrawnButton(double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (overButton(x, y, w, h))
	{
		if (MouseManager::leftClicked)
		{
			ShapeRenderer::drawRectangle(x, y, w, h, r / 2, g / 2, b / 2, a);
			return true;
		}
		ShapeRenderer::drawRectangle(x, y, w, h, r / 1.6, g / 1.6, b / 1.6, a);
		return false;
	}
	ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
	return false;
}

bool Button::clickedDrawnButton(int key, double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (overButton(x, y, w, h))
	{
		if (mouseKeyPressed(key))
		{
			ShapeRenderer::drawRectangle(x, y, w, h, r / 2, g / 2, b / 2, a);
			return true;
		}
		ShapeRenderer::drawRectangle(x, y, w, h, r / 1.6, g / 1.6, b / 1.6, a);
		return false;
	}
	ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
	return false;
}

bool Button::clickedDrawnButton(double x, double y, double w, double h, double r, double g, double b, double a, double r2, double g2, double b2, double a2)
{
	if (overButton(x, y, w, h))
	{
		if (MouseManager::leftClicked)
		{
			ShapeRenderer::drawRectangle(x, y, w, h, r2 / 2, g2 / 2, b2 / 2, a2);
			return true;
		}
		ShapeRenderer::drawRectangle(x, y, w, h, r2, g2, b2, a2);
		return false;
	}
	ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
	return false;
}

bool Button::clickedDrawnButton(int key, double x, double y, double w, double h, double r, double g, double b, double a, double r2, double g2, double b2, double a2)
{
	if (overButton(x, y, w, h))
	{
		if (mouseKeyPressed(key))
		{
			ShapeRenderer::drawRectangle(x, y, w, h, r2 / 2, g2 / 2, b2 / 2, a2);
			return true;
		}
		ShapeRenderer::drawRectangle(x, y, w, h, r2, g2, b2, a2);
		return false;
	}
	ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
	return false;
}

bool Button::clickedDrawnButton(double x, double y, double w, double h, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG)
{
	if (overButton(x, y, w, h))
	{
		overButtonIMG->setWH(w, h);
		overButtonIMG->draw(x, y);
		if (MouseManager::leftClicked)
		{
			return true;
		}
		return false;
	}
	outOfButtonIMG->setWH(w, h);
	outOfButtonIMG->draw(x, y);
	return false;
}

bool Button::clickedDrawnButton(int key, double x, double y, double w, double h, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG)
{
	if (overButton(x, y, w, h))
	{
		overButtonIMG->setWH(w, h);
		overButtonIMG->draw(x, y);
		if (mouseKeyPressed(key))
		{
			return true;
		}
		return false;
	}
	outOfButtonIMG->setWH(w, h);
	outOfButtonIMG->draw(x, y);
	return false;
}

bool Button::clickedDrawnButton(double x, double y, double w, double h, RenderIMG* clickButtonIMG, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG)
{
	if (overButton(x, y, w, h))
	{
		if (MouseManager::leftClicked)
		{
			clickButtonIMG->setWH(w, h);
			clickButtonIMG->draw(x, y);
			return true;
		}
		overButtonIMG->setWH(w, h);
		overButtonIMG->draw(x, y);
		return false;
	}
	outOfButtonIMG->setWH(w, h);
	outOfButtonIMG->draw(x, y);
	return false;
}

bool Button::clickedDrawnButton(int key, double x, double y, double w, double h, RenderIMG* clickButtonIMG, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG)
{
	if (overButton(x, y, w, h))
	{
		if (mouseKeyPressed(key))
		{
			clickButtonIMG->setWH(w, h);
			clickButtonIMG->draw(x, y);
			return true;
		}
		overButtonIMG->setWH(w, h);
		overButtonIMG->draw(x, y);
		return false;
	}
	outOfButtonIMG->setWH(w, h);
	outOfButtonIMG->draw(x, y);
	return false;
}

bool Button::buttonPressed(double x, double y, double w, double h, double r, double g, double b, double a)
{
	pressTimer -= RenderCore::rate;
	double divideFactor = 1;
	if (pressed)
	{
		divideFactor = 2;
	}
	if (Button::clickedDrawnButton(x, y, w, h, (r / divideFactor), (g / divideFactor), (b / divideFactor), a / divideFactor) && pressTimer < 0)
	{
		pressed = !pressed;
		pressTimer = 20;

	}
	return pressed;
}


bool Button::timeButtonClicked(double x, double y, double w, double h, double r, double g, double b, double a)
{
	pressTimer -= RenderCore::rate;
	double divideFactor = 1;
	if (Button::clickedDrawnButton(x, y, w, h, (r), (g), (b), a) && pressTimer < 0)
	{
		pressTimer = 40;
		return true;
	}
	return false;
}

bool Button::timeButtonClicked(bool aboveLayer, double x, double y, double w, double h, double r, double g, double b, double a)
{
	pressTimer -= RenderCore::rate;
	if (Button::clickedDrawnButton(true, x, y, w, h, (r), (g), (b), a) && pressTimer < 0)
	{
		pressTimer = 17;
		return true;

	}
	return false;
}

bool Button::mouseKeyPressed(int key)
{
	if (key == 0 && MouseManager::leftClicked)
	{
		return true;
	}
	else if (key == 1 && MouseManager::rightClicked)
	{
		return true;
	}
	else if (MouseManager::middleClicked)
	{
		return true;
	}
	return false;
}

Button::~Button()
{
}