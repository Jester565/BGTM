#include "KeyManager.h"
#include "RenderCore.h"
#include <iostream>
#include "TextField.h"

KeyManager::KeyManager()
{
}

std::list<SDL_Keycode> KeyManager::keys;

std::vector<std::string> KeyManager::pressedKeys;

bool KeyManager::isPressed()
{
	return pressed;
}
bool KeyManager::keyPressed(std::string checkKey)
{
	std::list<int>::const_iterator iterator;
	for (iterator = keys.begin(); iterator != keys.end(); ++iterator) {
		std::string itKey = SDL_GetKeyName(*iterator);
		if (itKey == checkKey)
		{
			return true;
		}
	}
	return false;
}

bool KeyManager::keyHeld(std::string checkKey)
{
	for (int i = 0; i < pressedKeys.size(); i++)
	{
		if (pressedKeys.at(i) == checkKey)
		{
			return true;
		}
	}
	return false;
}

void KeyManager::clearList()
{
	keys.clear();
}

bool KeyManager::pressed = false;

bool KeyManager::update(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (TextField::activeField != NULL)
		{
			TextField::activeField->update(e);
		}
		SDL_Keycode sdlkc = e->key.keysym.sym;
		keys.push_back(sdlkc);
		std::string stringKey = SDL_GetKeyName(sdlkc);
		bool found = false;
		for (int i = 0; i < pressedKeys.size(); i++)
		{
			if (stringKey == pressedKeys.at(i))
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			pressedKeys.push_back(stringKey);
		}
		pressed = true;
		return true;
	}
	else if (e->type == SDL_KEYUP)
	{
		std::string key = SDL_GetKeyName(e->key.keysym.sym);
		for (int i = 0; i < pressedKeys.size(); i++)
		{
			if (key == pressedKeys.at(i))
			{
				pressedKeys.erase(pressedKeys.begin() + i);
			}
		}
		pressed = true;
		return true;
	}
	else if (TextField::activeField != NULL && e->type == SDL_TEXTINPUT)
	{
		TextField::activeField->update2(e);
	}
	pressed = false;
	return false;
}

KeyManager::~KeyManager()
{
	keys.clear();
}
