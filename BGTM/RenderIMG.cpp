#include "RenderIMG.h"
#include "RenderCore.h"
#include <iostream>

std::vector <RenderIMG*> RenderIMG::imgPointers;

void RenderIMG::reconfigureImagesToRenderer()
{
	for (int i = 0; i < imgPointers.size(); i++)
	{
		imgPointers[i]->reloadImages();
	}
}
RenderIMG::RenderIMG(std::string path)
{
	savedSurface = NULL;
	imgPointerIndex = imgPointers.size();
	imgPointers.push_back(this);
	configureTexture(path);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

RenderIMG::RenderIMG(SDL_Texture* textureParam, int imageW, int imageH)
{
	savedSurface = NULL;
	imgPointerIndex = imgPointers.size();
	imgPointers.push_back(this);
	iW = imageW;
	iH = imageH;
	texture = textureParam;
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

RenderIMG::RenderIMG(SDL_Surface* surfaceParam)
{
	savedSurface = NULL;
	imgPointerIndex = imgPointers.size();
	imgPointers.push_back(this);
	configureSurface(surfaceParam);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void RenderIMG::resetImage(std::string path)
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	configureTexture(path);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void RenderIMG::resetImage(SDL_Surface* surface)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	if (surface != NULL)
	{
		configureSurface(surface);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}
}

void RenderIMG::resetImage(SDL_Texture* textureParam, int imageW, int imageH)
{
	iW = imageW;
	iH = imageH;
	SDL_DestroyTexture(texture);
	texture = NULL;
	texture = textureParam;
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void RenderIMG::configureTexture(std::string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	configureSurface(loadedSurface);
}

void RenderIMG::configureSurface(SDL_Surface* loadedSurface)
{
	if (savedSurface != NULL)
		SDL_FreeSurface(savedSurface);
	iW = loadedSurface->w;
	iH = loadedSurface->h;
	w = iW;
	h = iH;
	savedSurface = loadedSurface;
	texture = SDL_CreateTextureFromSurface(RenderCore::getRenderer(), loadedSurface);
	if (texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", SDL_GetError());
	}
}

void RenderIMG::reloadImages()
{
	texture = SDL_CreateTextureFromSurface(RenderCore::getRenderer(), savedSurface);
	if (texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", SDL_GetError());
	}
}

void RenderIMG::draw()
{
	if (!RenderCore::minimized)
	{
		if (rotPoint != NULL)
		{
			if (offRotMode == 1)
			{
				rotPoint->x = (int)((xOffRot * (w / iW) + w / 2) * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
				rotPoint->y = (int)(-(yOffRot * (h / iH) - h / 2) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
			}
			else if (offRotMode == 2)
			{
				rotPoint->x = (int)((xOffRot * (w / iW)) * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
				rotPoint->y = (int)(-(yOffRot * (h / iH)) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
			}
			else if (offRotMode == 3)
			{
				rotPoint->x = (int)((xOffRot * (w / iW)) * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
				rotPoint->y = (int)(-(yOffRot * (h / iH) - h) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
			}
			else if (offRotMode == 4)
			{
				rotPoint->x = (int)((xOffRot * (w / iW) + w) * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
				rotPoint->y = (int)(-(yOffRot * (h / iH) - h) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
			}
			else
			{
				rotPoint->x = (int)((xOffRot * (w / iW) + w) * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH));
				rotPoint->y = (int)(-(yOffRot * (h / iH)) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT));
			}
		}
		SDL_Rect renderQuad = { (int)(x * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH)), (int)(RenderCore::screenHeight - (y + h) * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT)),
			(int)(w * (RenderCore::screenWidth / RenderCore::STANDARD_WIDTH)), (int)(h * (RenderCore::screenHeight / RenderCore::STANDARD_HEIGHT)) };
		SDL_RenderCopyEx(RenderCore::getRenderer(), texture, NULL, &renderQuad, angle, rotPoint, flipMode);
	}
}

void RenderIMG::draw(double x, double y)
{
	setXY(x, y);
	draw();
}

void RenderIMG::draw(double x, double y, double w, double h)
{
	setXY(x, y);
	setWH(w, h);
	draw();
}

void RenderIMG::drawCentered(double x, double y, double w, double h)
{
	setXY(x - w / 2, y - h / 2);
	setWH(w, h);
	draw();
}

void RenderIMG::setRotationPointFromCenter(double xOff, double yOff)
{
	if (rotPoint == NULL)
	{
		rotPoint = new SDL_Point();
	}
	offRotMode = 1;
	xOffRot = xOff;
	yOffRot = yOff;
}

void RenderIMG::setRotationPointFromTopLeft(double xOff, double yOff)
{
	if (rotPoint == NULL)
	{
		rotPoint = new SDL_Point();
	}
	offRotMode = 2;
	xOffRot = xOff;
	yOffRot = yOff;
}

void RenderIMG::setRotationPointFromBottomLeft(double xOff, double yOff)
{
	if (rotPoint == NULL)
	{
		rotPoint = new SDL_Point();
	}
	offRotMode = 3;
	xOffRot = xOff;
	yOffRot = yOff;
}

void RenderIMG::setRotationPointFromBottomRight(double xOff, double yOff)
{
	if (rotPoint == NULL)
	{
		rotPoint = new SDL_Point();
	}
	offRotMode = 4;
	xOffRot = xOff;
	yOffRot = yOff;
}

void RenderIMG::setRotationPointFromTopRight(double xOff, double yOff)
{
	if (rotPoint == NULL)
	{
		rotPoint = new SDL_Point();
	}
	offRotMode = 5;
	xOffRot = xOff;
	yOffRot = yOff;
}

RenderIMG::~RenderIMG()
{
	imgPointers.erase(imgPointers.begin() + imgPointerIndex);
	SDL_DestroyTexture(texture);
	delete rotPoint;
	rotPoint = NULL;
	texture = NULL;
}
