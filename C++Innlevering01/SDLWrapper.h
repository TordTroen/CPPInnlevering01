#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include "Color.h"

struct Image
{
	SDL_Texture* texture;
	SDL_Rect rect;
};

class SDLWrapper
{
public:
	SDLWrapper();
	~SDLWrapper();
	int InitializeWindow(int screenWidth, int screenHeight, Color bgColor); // TODO Add color
	Image* CreateImage(std::string filename);
	void RenderImages(bool clearPrevious) const;
	SDL_Window* GetSDL_Window() const { return window; }
	SDL_Surface* GetSDL_Surface() const { return screenSurface; }
	SDL_Renderer* GetSDL_Renderer() const { return renderer; }
private:
	void DestroyImages();
	void DrawImage(Image *img) const;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::vector<Image*> allImages;
};
