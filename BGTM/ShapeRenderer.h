#pragma once
#include <map>
#include <SDL_ttf.h>
class ShapeRenderer
{
public:
	ShapeRenderer();
	static void drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a);
	static void drawLine(double x, double y, double x2, double y2, double r, double g, double b, double a);
	static void drawRectangleFill(double x, double y, double w, double h, double r, double g, double b, double a);
	static void drawRectangleOutline(double x, double y, double w, double h, double r, double g, double b, double a);
	static void drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a, double oR, double oG, double oB, double oA);
	~ShapeRenderer();
private:
	static bool drawOn();
	static int modX(double x);
	static int modY(double y, double h);
	static int modW(double w);
	static int modH(double w);
};

