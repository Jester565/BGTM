#pragma once
#include "MouseManager.h"
#include "ShapeRenderer.h"
#include "RenderIMG.h"

class Button
{
public:
	Button();

	static bool overButton(double x, double y, double w, double h);

	static bool clickedButton(double x, double y, double w, double h);

	static bool clickedButton(int key, double x, double y, double w, double h);

	static bool clickedDrawnButton(double x, double y, double w, double h, double r, double g, double b, double a);

	static bool clickedDrawnButton(int key, double x, double y, double w, double h, double r, double g, double b, double a);

	static bool clickedDrawnButton(double x, double y, double w, double h, double r, double g, double b, double a, double r2, double g2, double b2, double a2);

	static bool clickedDrawnButton(int key, double x, double y, double w, double h, double r, double g, double b, double a, double r2, double g2, double b2, double a2);

	static bool clickedDrawnButton(double x, double y, double w, double h, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG);

	static bool clickedDrawnButton(int key, double x, double y, double w, double h, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG);

	static bool clickedDrawnButton(double x, double y, double w, double h, RenderIMG* clickButtonIMG, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG);

	static bool clickedDrawnButton(int key, double x, double y, double w, double h, RenderIMG* clickButtonIMG, RenderIMG* overButtonIMG, RenderIMG* outOfButtonIMG);

	bool buttonPressed(double x, double y, double w, double h, double r, double g, double b, double a);

	static bool overButton(bool aboveLayer, double x, double y, double w, double h);

	static bool clickedButton(bool aboveLayer, double x, double y, double w, double h);

	static bool clickedDrawnButton(bool aboveLayer, double x, double y, double w, double h, double r, double g, double b, double a);

	static void setOverLay(bool mode);

	bool timeButtonClicked(double x, double y, double w, double h, double r, double g, double b, double a);

	bool timeButtonClicked(bool above, double x, double y, double w, double h, double r, double g, double b, double a);

	bool isPressed()
	{
		return pressed;
	}

	void changePressed()
	{
		pressed = !pressed;
	}

	void setPressed(bool mode)
	{
		pressed = mode;
	}

	~Button();
private:

	static bool overLayered;

	bool pressed = false;

	double pressTimer = 0;

	static bool mouseKeyPressed(int key);

};



