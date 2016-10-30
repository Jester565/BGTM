#include "RenderCore.h"
#include <SDL_ttf.h>
#include <windows.h>
#include <wtypes.h>
#include "MouseManager.h"
#include "KeyManager.h"
#include "Sound.h"
#include <SDL_mixer.h>
#include "TextField.h"
#include <thread>

char RenderCore::m_RebootWindowKey = '\0';

bool RenderCore::windowDown = false;

RenderCore::RenderCore(char rebootWindowKey)
{
	m_RebootWindowKey = rebootWindowKey;
	if (rebootWindowKey != '\0' && RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, 0x42))
		std::cout << "bound hot key" << std::endl;
}

SDL_Window* RenderCore::gWindow = NULL;

SDL_Renderer* RenderCore::gRenderer = NULL;

const double RenderCore::STANDARD_HEIGHT = 1080;

const double RenderCore::STANDARD_WIDTH = 1920;

bool RenderCore::inputSet = false;

bool RenderCore::running = true;

SDL_Renderer* RenderCore::getRenderer()
{
	return gRenderer;
}

SDL_Window* RenderCore::getWindow()
{
	return gWindow;
}

int RenderCore::screenWidth = 0;

int RenderCore::screenHeight = 0;

void RenderCore::shutDown()
{
	running = false;
}

double RenderCore::rate = 0;

double RenderCore::timePassed = 0;

bool RenderCore::minimized = false;

void RenderCore::run()
{
	SDL_Event e;
	if (init())
	{
		OutputDebugStringW(L"Start\n");
		printf("init was sucessful!\n");
		while (running)
		{
			if (!windowDown)
			{
				if (!inputSet && TextField::activeField != NULL)
				{
					SDL_StartTextInput();
					inputSet = true;
				}
				timePassed = SDL_GetTicks() - lastTime;
				lastTime = SDL_GetTicks();
				rate = timePassed / 16.66667;
				KeyManager::clearList();
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						if (m_RebootWindowKey == '\0')
							shutDown();
						else
						{
							windowDown = true;
							destroyWindow();
						}
					}
					else if (e.window.event == SDL_WINDOWEVENT_MINIMIZED)
					{
						minimized = true;
					}
					else if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
					{
						SDL_RestoreWindow(gWindow);
						SDL_UpdateWindowSurface(gWindow);
						std::cout << "Called" << std::endl;
						minimized = false;
						restoreNeeded = true;
						int x;
						int y;
					}
					else if (KeyManager::update(&e))
					{

					}
					else if (MouseManager::update(&e))
					{

					}
				}
				if (restoreNeeded)
				{
					restoreTimer++;
					if (restoreTimer > 70)
					{
						SDL_RestoreWindow(gWindow);
						SDL_UpdateWindowSurface(gWindow);
						restoreTimer = 0;
						restoreNeeded = false;
					}
				}
				SDL_RenderClear(gRenderer);
				SDL_GetWindowSize(gWindow, &screenWidth, &screenHeight);
				draw();

				if (inputSet && TextField::activeField == NULL)
				{
					SDL_StopTextInput();
					inputSet = false;
				}
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderPresent(gRenderer);
			}
			else
			{
				timePassed = SDL_GetTicks() - lastTime;
				lastTime = SDL_GetTicks();
				rate = timePassed / 16.66667;
				draw();
				//std::cout << "Calling";
				MSG msg = { 0 };
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_HOTKEY)
					{
						std::cout << "Hotkey registered" << std::endl;
						createWindow();
						windowDown = false;
						RenderIMG::reconfigureImagesToRenderer();
						break;
					}
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			}
		}
	}
	else
	{
		printf("init was not sucessful");
	}
}

bool RenderCore::init()
{
	if (!createWindow())
		return false;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SLD Image Error: ", IMG_GetError);
		return false;
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_ttf Error: %s\n", Mix_GetError);
		return false;
	}
	return true;
}

bool RenderCore::createWindow()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int screenWidth = desktop.right;
	int screenHeight = desktop.bottom;
	if (windowDown)
		std::cout << "doggy";
	gWindow = SDL_CreateWindow("SDL Tutorial", 5, 30, screenWidth - 10, screenHeight - 75, SDL_WINDOW_RESIZABLE);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: ", SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: ", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	return true;
}

void RenderCore::destroyWindow()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}

void RenderCore::draw()
{

}

RenderCore::~RenderCore()
{
	Sound::musicDestroy();
	destroyWindow();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
