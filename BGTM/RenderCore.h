#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class RenderCore
{
public:
	RenderCore(char rebootWindowKey = '\0');
	void run();
	static SDL_Window* getWindow();
	static bool inputSet;
	static double rate;
	static double timePassed;
	static void shutDown();
	static SDL_Renderer* getRenderer();
	static int screenWidth;
	static int screenHeight;
	static bool minimized;
	static char m_RebootWindowKey;
	const static double STANDARD_WIDTH;
	const static double STANDARD_HEIGHT;
	~RenderCore();
protected:
	virtual bool init();
	virtual void draw();
	double restoreTimer = 0;
	bool restoreNeeded = false;
	static SDL_Renderer *gRenderer;
	static bool running;
	static bool windowDown;
private:
	static SDL_Window *gWindow;
	static void destroyWindow();
	static bool createWindow();
	Uint32 lastTime;
};
