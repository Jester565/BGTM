#pragma once
#include <list>
#include <iterator>
#include <SDL.h>
#include <vector>

class KeyManager
{
public:
	KeyManager();
	static bool keyPressed(std::string checkKey);
	static bool keyHeld(std::string checkKey);
	static bool update(SDL_Event* e);
	static void clearList();
	static bool isPressed();
	~KeyManager();
private:
	static std::vector <std::string> pressedKeys;
	static std::list <SDL_Keycode> keys;
	static bool pressed;
};
