#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include "Color.h"
#include "Drawable.h"

class SDLWrapper
{
public:
	SDLWrapper();
	~SDLWrapper();
	int InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor);
	Drawable* CreateImage(std::string filename);
	Drawable* CreateText(std::string text, SDL_Color color, int x, int w);
	void RenderImages(bool clearPrevious) const;
	SDL_Window* GetSDL_Window() const { return window; }
	SDL_Surface* GetSDL_Surface() const { return screenSurface; }
	SDL_Renderer* GetSDL_Renderer() const { return renderer; }
private:
	void DestroyImages();
	void RenderDrawable(Drawable* drawable) const;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::vector<Drawable*> allDrawables;
	TTF_Font* font;
};
