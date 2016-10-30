#include "MouseManager.h"
#include "RenderCore.h"
#include <iostream>

MouseManager::MouseManager()
{
}

int MouseManager::x = 0;

int MouseManager::y = 0;

bool MouseManager::left = false;

bool MouseManager::right = false;

bool MouseManager::middle = false;

bool MouseManager::leftClicked = false;

bool MouseManager::rightClicked = false;

bool MouseManager::middleClicked = false;

bool MouseManager::isMoved()
{
	return moved;
}

bool MouseManager::moved = false;

bool MouseManager::update(SDL_Event* e)
{
	leftClicked = false;
	rightClicked = false;
	middleClicked = false;
	if (e->type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&x, &y);
		x = (x * (RenderCore::STANDARD_WIDTH / ((double)RenderCore::screenWidth)));
		y = ((RenderCore::screenHeight - y) * (RenderCore::STANDARD_HEIGHT / ((double)RenderCore::screenHeight)));
		moved = true;
		return true;
	}
	else if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			left = true;
			leftClicked = true;
		}
		else if (e->button.button == SDL_BUTTON_RIGHT)
		{
			right = true;
			rightClicked = true;
		}
		else if (e->button.button == SDL_BUTTON_MIDDLE)
		{
			middle = true;
			middleClicked = true;
		}
		moved = true;
		return true;
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			left = false;
		}
		else if (e->button.button == SDL_BUTTON_RIGHT)
		{
			right = false;
		}
		else if (e->button.button == SDL_BUTTON_MIDDLE)
		{
			middle = false;
		}
		moved = true;
		return true;
	}
	moved = false;
	return false;
}

MouseManager::~MouseManager()
{
}
