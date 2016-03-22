#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include "Color.h"

struct Image
{
	SDL_Texture* texture;
	SDL_Rect rect;
};

struct Text
{
	SDL_Texture* texture;
	SDL_Rect rect;
};

class SDLWrapper
{
public:
	SDLWrapper();
	~SDLWrapper();
	int InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor);
	Image* CreateImage(std::string filename);
	Text* CreateText(std::string text, SDL_Color color, int x, int w);
	void RenderImages(bool clearPrevious) const;
	SDL_Window* GetSDL_Window() const { return window; }
	SDL_Surface* GetSDL_Surface() const { return screenSurface; }
	SDL_Renderer* GetSDL_Renderer() const { return renderer; }
private:
	void DestroyImages();
	void DrawImage(Image *img) const;
	void DrawText(Text* txt) const;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::vector<Image*> allImages;
	std::vector<Text*> allTexts;
	TTF_Font* font;
};
