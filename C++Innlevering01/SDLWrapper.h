#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include <SDL_image.h>
#include <string>
#include <deque> 
#include <memory>
#include "Color.h"
#include "Drawable.h"

class SDLWrapper
{
public:
	~SDLWrapper();

	/* Initialized the SDL libraries, and creates a new SDL window with the specified parameters. */
	int InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor);

	/* Creates an image from the filename with the specified rect. If originalSize if true, the image will have the size of the original imagefile. */
	Drawable* CreateImage(std::string filename, Rect rect, bool originalSize = true, bool renderUnderneath = false);

	/* Creates an image from the filename with the specified rect. The color will be applied ontop of the image. If originalSize if true, the image will have the size of the original imagefile. */
	Drawable* CreateImage(std::string filename, Rect rect, Color color, bool originalSize = true, bool renderUnderneath = false);

	/* Creates a rect with the specified color and rect. */
	Drawable* CreateRect(Color color, Rect rect, bool renderUnderneath = false);

	/* Creates text with the specified text, color and rect. If originalSize is true, the text will have the width/height applied based on the text length/font size. */
	Drawable* CreateText(std::string text, Color color, Rect rect, bool originalSize = true, bool renderUnderneath = false);

	/* Renders all the images created with the CreateXXX functions. clearPrevious decides if the screen will be cleared before rendering. */
	void RenderImages(bool clearPrevious) const;

	void SetTextureColor(SDL_Texture* texture, Color color);

	void DeleteDrawable(Drawable* drawable);
private:
	void Init();
	void DestroyImages();
	void RenderDrawable(const Drawable* const drawable) const;
	void AddDrawableToCollection(Drawable* drawable, bool renderUnderneath);
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::deque<std::unique_ptr<Drawable>> allDrawables;
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

