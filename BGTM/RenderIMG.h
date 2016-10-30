#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
class RenderIMG
{
public:
	RenderIMG(std::string path);
	RenderIMG(SDL_Surface* surface);
	RenderIMG(SDL_Texture* texture, int imageW, int imageH);
	void resetImage(std::string path);
	void resetImage(SDL_Texture* texture, int imageW, int imageH);
	void resetImage(SDL_Surface* surface);
	void draw();
	void draw(double x, double y);
	void setX(double x);
	void setY(double y);
	void setXY(double x, double y);
	void setW(double w);
	void setH(double h);
	void setWH(double w, double h);
	void setXScale(double sX);
	void setYScale(double sY);
	void setScale(double scale);
	void setXYScale(double sX, double sY);
	void setAlpha(double alpha);
	void setAngle(double degs);
	void setRadians(double rads);
	void setVFlip();
	void setHFlip();
	void flipOff();
	void draw(double x, double y, double w, double h);
	void drawCentered(double x, double y, double w, double h);
	void setRotationPointFromTopLeft(double xOff, double yOff);
	void setRotationPointFromBottomLeft(double xOff, double yOff);
	void setRotationPointFromTopRight(double xOff, double yOff);
	void setRotationPointFromBottomRight(double xOff, double yOff);
	void setRotationPointFromCenter(double xOff, double yOff);
	int imgPointerIndex;
	static void reconfigureImagesToRenderer();
	~RenderIMG();
private:
	SDL_Texture* texture;
	SDL_Surface* savedSurface;
	void reloadImages();
	double x;
	double y;
	double iW;
	double iH;
	double w;
	double h;
	double angle;
	double xOffRot;
	double yOffRot;
	int offRotMode;
	SDL_Point* rotPoint;
	SDL_RendererFlip flipMode;
	void configureTexture(std::string path);
	void configureSurface(SDL_Surface* surface);
	static std::vector <RenderIMG*> imgPointers;
};

inline void RenderIMG::setW(double paramW)
{
	w = paramW;
}

inline void RenderIMG::setH(double paramH)
{
	h = paramH;
}

inline void RenderIMG::setWH(double paramW, double paramH)
{
	w = paramW;
	h = paramH;
}

inline void RenderIMG::setScale(double s)
{
	w = s * iW;
	h = s * iH;
}

inline void RenderIMG::setXScale(double xS)
{
	w = xS * iW;
}

inline void RenderIMG::setYScale(double yS)
{
	h = yS * iH;
}

inline void RenderIMG::setXYScale(double xS, double yS)
{
	w = xS * iW;
	h = yS * iH;
}

inline void RenderIMG::setX(double paramX)
{
	x = paramX;
}

inline void RenderIMG::setY(double paramY)
{
	y = paramY;
}

inline void RenderIMG::setXY(double paramX, double paramY)
{
	x = paramX;
	y = paramY;
}

inline void RenderIMG::setAlpha(double alpha)
{
	SDL_SetTextureAlphaMod(texture, (int)alpha);
}

inline void RenderIMG::setAngle(double paramAngle)
{
	angle = paramAngle;
}

inline void RenderIMG::setRadians(double paramRadian)
{
	angle = paramRadian*(180 / M_PI);
}

inline void RenderIMG::setVFlip()
{
	flipMode = SDL_FLIP_VERTICAL;
}

inline void RenderIMG::flipOff()
{
	flipMode = SDL_FLIP_NONE;
}

inline void RenderIMG::setHFlip()
{
	flipMode = SDL_FLIP_HORIZONTAL;
}

