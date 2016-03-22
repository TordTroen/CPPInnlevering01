#include "SDLWrapper.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

SDLWrapper::SDLWrapper()
{
	font = NULL;
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;
}

SDLWrapper::~SDLWrapper()
{
	DestroyImages();
	SDL_DestroyWindow(GetSDL_Window());
	SDL_DestroyRenderer(GetSDL_Renderer());

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int SDLWrapper::InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor)
{
	cout << "Width: " << screenWidth << endl;
	int retStatus = 0;
	int imgFlags = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL initialization failed!" << endl;
		retStatus = 1;
	}
	else if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << "SDL_IMG initialization failed!" << endl;
		retStatus = 1;
	}
	else if (TTF_Init() != 0)
	{
		cout << "SDL_TTF initialization failed!" << endl;
		retStatus = 1;
	}
	else
	{
		cout << "SDL with SDL_IMG and SDL_TTF initialized..." << endl << endl;

		// Initialize font
		font = TTF_OpenFont("arial.ttf", 28);
		if (font == NULL)
		{
			cout << "Failed to load font: " << TTF_GetError() << endl;
			retStatus = 1;
		}

		// Make window
		window = SDL_CreateWindow(windowName.c_str(), 300, 50, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (window == NULL) {
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			retStatus = 1;
		}
		else {
			// Draw white box in window, then wait 5 secs (so we have time to see it).
			//screenSurface = SDL_GetWindowSurface(window);
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0xFB, 0x1F));
			//SDL_UpdateWindowSurface(window);

			//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == NULL)
			{
				cout << "Failed to create renderer, details: " << SDL_GetError() << endl;
				retStatus = 1;
			}

			SDL_SetRenderDrawColor(renderer, bgColor.GetR(), bgColor.GetG(), bgColor.GetB(), bgColor.GetA());
			SDL_RenderClear(renderer);
		}
	}
	return retStatus;
}

// TODO Actually use status variable to check for fails before trying to us the objects
Drawable* SDLWrapper::CreateImage(std::string filename)
{
	SDL_Surface* image = IMG_Load(filename.c_str());
	int status = 0;

	if (image == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		status = 1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetSDL_Renderer(), image);

	if (texture == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		status = 1;
	}

	SDL_Rect rect;
	rect.h = image->h;
	rect.w = image->w;
	rect.x = 0;
	rect.y = 0;

	SDL_FreeSurface(image);

	Drawable* drawable = new Drawable(Rect(0, 0, image->w, image->h), texture);
	allDrawables.emplace_back(drawable);
	return drawable;
}

Drawable* SDLWrapper::CreateText(std::string text, SDL_Color color, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = NULL;
	if (textSurface == NULL)
	{
		cout << "Couldn' make surface for rendering text '" << text << "'." << endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			cout << "Error creating texture for text" << endl;
		}

		SDL_FreeSurface(textSurface);
	}
	//allTexts.emplace_back(txt);
	//return txt;
	Drawable* drawable = new Drawable(Rect(0, 0, textSurface->w, textSurface->h), texture);
	allDrawables.emplace_back(drawable);
	return drawable;
}

void SDLWrapper::RenderImages(bool clearPrevious) const
{
	if (clearPrevious)
	{
		SDL_RenderClear(GetSDL_Renderer());
	}
	for (auto i : allDrawables)
	{
		RenderDrawable(i);
	}
	SDL_RenderPresent(GetSDL_Renderer());
}

void SDLWrapper::DestroyImages()
{
	for (auto i : allDrawables)
	{
		// TODO possibly make Image a class with its own destructor that destroys the texture(the destructor is called when the vector is destroyed)
		SDL_DestroyTexture(i->GetTexture());
		delete i;
	}
}

void SDLWrapper::RenderDrawable(Drawable* drawable) const
{
	SDL_RenderCopy(GetSDL_Renderer(), drawable->GetTexture(), NULL, &drawable->rect.ToSDL_Rect());
}
