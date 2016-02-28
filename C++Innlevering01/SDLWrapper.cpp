#include "SDLWrapper.h"
#include <iostream>
#include <SDL_image.h>
using namespace std;

SDLWrapper::SDLWrapper()
{
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;
}

SDLWrapper::~SDLWrapper()
{
	SDL_Quit();
	DestroyImages();
	SDL_DestroyWindow(GetSDL_Window());
	SDL_DestroyRenderer(GetSDL_Renderer());
}

int SDLWrapper::InitializeWindow(int screenWidth, int screenHeight, Color bgColor)
{
	int retStatus = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL initialization failed" << endl;
		retStatus = 1;
	}
	else
	{
		cout << "SDL initialized..." << endl << endl;

		window = SDL_CreateWindow("SDL Tutorial", 480, 64, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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
				std::cerr << "Failed to create renderer, details: " << SDL_GetError() << std::endl;
				retStatus = 1;
			}

			SDL_SetRenderDrawColor(renderer, bgColor.GetR(), bgColor.GetG(), bgColor.GetB(), bgColor.GetA());
			SDL_RenderClear(renderer);
		}
	}
	return retStatus;
}

Image* SDLWrapper::CreateImage(std::string filename)
{
	Image *img = new Image();

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
	rect.x = 10;
	rect.y = 10;

	SDL_FreeSurface(image);

	allImages.emplace_back(img);
	img->texture = texture;
	img->rect = rect;
	return img;
}

void SDLWrapper::RenderImages(bool clearPrevious) const
{
	if (clearPrevious)
	{
		SDL_RenderClear(GetSDL_Renderer());
	}
	for (auto i : allImages)
	{
		DrawImage(i);
	}
	SDL_RenderPresent(GetSDL_Renderer());
}

void SDLWrapper::DestroyImages()
{
	for (auto i : allImages)
	{
		// TODO possibly make Image a class with its own destructor that destroys the texture(the destructor is called when the vector is destroyed)
		SDL_DestroyTexture(i->texture);
		delete i;
	}
}

void SDLWrapper::DrawImage(Image *img) const
{
	SDL_RenderCopy(GetSDL_Renderer(), img->texture, NULL, &img->rect);
}
