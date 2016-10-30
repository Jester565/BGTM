#pragma once
#include <SDL.h>
class MouseManager
{
public:
	MouseManager();
	static int x;
	static int y;
	static bool left;
	static bool right;
	static bool middle;
	static bool leftClicked;
	static bool rightClicked;
	static bool middleClicked;
	static bool update(SDL_Event* e);
	static bool isMoved();
	static int scrollAmount();
	~MouseManager();
private:
	static bool moved;
};
