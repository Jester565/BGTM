#include "ShapeRenderer.h"
#include "RenderCore.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

ShapeRenderer::ShapeRenderer()
{

}

bool ShapeRenderer::drawOn()
{
	return true;
}
int ShapeRenderer::modX(double x)
{
	if (drawOn()){
		return (int)(x * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
	}
	return false;
}

int ShapeRenderer::modY(double y, double h)
{
	if (drawOn())
	{
		return (int)(RenderCore::screenHeight - (y + h) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
	}
}

int ShapeRenderer::modW(double w)
{
	if (drawOn())
	{
		return (int)(w * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
	}
}

int ShapeRenderer::modH(double h)
{
	if (drawOn())
	{
		return (int)(h * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
	}
}

void ShapeRenderer::drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a, double oR, double oG, double oB, double oA)
{
	if (drawOn())
	{
		SDL_Rect fillRect{ modX(x), modY(y, h), modW(w), modH(h) };
		std::cout << modX(x) << modY(y, h) << modW(w) << modH(h);
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(r), (int)(g), (int)(b), (int)(a));
		SDL_RenderFillRect(RenderCore::getRenderer(), &fillRect);
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(oR), (int)(oG), (int)(oB), (int)(oA));
		SDL_RenderDrawRect(RenderCore::getRenderer(), &fillRect);
	}
}

void ShapeRenderer::drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (drawOn())
	{
		SDL_Rect fillRect{ modX(x), modY(y, h), modW(w), modH(h) };
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(r), (int)(g), (int)(b), (int)a);
		SDL_RenderFillRect(RenderCore::getRenderer(), &fillRect);
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(RenderCore::getRenderer(), &fillRect);
	}
}

void ShapeRenderer::drawRectangleFill(double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (drawOn())
	{
		SDL_Rect fillRect{ modX(x), modY(y, h), modW(w), modH(h) };
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(r), (int)(g), (int)(b), (int)(a));
		SDL_RenderFillRect(RenderCore::getRenderer(), &fillRect);
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(RenderCore::getRenderer(), &fillRect);
	}
}

void ShapeRenderer::drawRectangleOutline(double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (drawOn())
	{
		SDL_Rect fillRect{ modX(x), modY(y, h), modW(w), modH(h) };
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(r), (int)(g), (int)(b), (int)(a));
		SDL_RenderDrawRect(RenderCore::getRenderer(), &fillRect);
	}
}

void ShapeRenderer::drawLine(double x, double y, double x2, double y2, double r, double g, double b, double a)
{
	if (drawOn())
	{
		SDL_SetRenderDrawColor(RenderCore::getRenderer(), (int)(r), (int)(g), (int)(b), (int)(a));
		SDL_RenderDrawLine(RenderCore::getRenderer(), modX(x), modY(y, 0), modX(x2), modY(y2, 0));
	}
}

ShapeRenderer::~ShapeRenderer()
{
}
