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
	~SDLWrapper();
	int InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor);
	Drawable* CreateImage(std::string filename, Rect rect, bool originalSize = true);
	Drawable* CreateImage(std::string filename, Rect rect, Color color, bool originalSize = true);
	Drawable* CreateRect(Color color, Rect rect);
	Drawable* CreateText(std::string text, Color color, Rect rect, bool originalSize = true);
	void RenderImages(bool clearPrevious) const;
	SDL_Window* GetSDL_Window() const { return window; }
	SDL_Surface* GetSDL_Surface() const { return screenSurface; }
	SDL_Renderer* GetSDL_Renderer() const { return renderer; }
	void SetTextureColor(SDL_Texture* texture, Color color);
private:
	void Init();
	void DestroyImages();
	void RenderDrawable(Drawable* drawable) const;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::vector<Drawable*> allDrawables;
	TTF_Font* font;

// Singleton stuff
public:
	static SDLWrapper& GetInstance()
	{
		static SDLWrapper instance;
		return instance;
	}
private:
	SDLWrapper() {};
	SDLWrapper(SDLWrapper const&);
	void operator=(SDLWrapper const&);
};
