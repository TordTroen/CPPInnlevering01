#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include <SDL_image.h>
#include <string>
#include <vector>
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
	std::shared_ptr<Drawable> CreateImage(std::string filename, Rect rect, bool originalSize = true);
	/* Creates an image from the filename with the specified rect. The color will be applied ontop of the image. If originalSize if true, the image will have the size of the original imagefile. */
	std::shared_ptr<Drawable> CreateImage(std::string filename, Rect rect, Color color, bool originalSize = true);
	/* Creates a rect with the specified color and rect. */
	std::shared_ptr<Drawable> CreateRect(Color color, Rect rect);
	/* Creates text with the specified text, color and rect. If originalSize is true, the text will have the width/height applied based on the text length/font size. */
	std::shared_ptr<Drawable> CreateText(std::string text, Color color, Rect rect, bool originalSize = true);
	/* Renders all the images created with the CreateXXX functions. clearPrevious decides if the screen will be cleared before rendering. */
	void RenderImages(bool clearPrevious) const;
	//SDL_Window* GetSDL_Window() const { return window; }
	//SDL_Surface* GetSDL_Surface() const { return screenSurface; }
	//SDL_Renderer* GetSDL_Renderer() const { return renderer; }
	void SetTextureColor(SDL_Texture* texture, Color color);
private:
	void Init();
	void DestroyImages();
	void RenderDrawable(std::shared_ptr<Drawable> drawable) const;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	std::vector<std::shared_ptr<Drawable>> allDrawables;
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

