#include "SDLWrapper.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

SDLWrapper::~SDLWrapper()
{
	DestroyImages();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int SDLWrapper::InitializeWindow(std::string windowName, int screenWidth, int screenHeight, Color bgColor)
{
	int retStatus = 0;
	int imgFlags = IMG_INIT_JPG;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL initialization failed!" << endl;
		return 1;
	}
	else if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << "SDL_IMG initialization failed!" << endl;
		return 1;
	}
	else if (TTF_Init() != 0)
	{
		cout << "SDL_TTF initialization failed!" << endl;
		return 1;
	}


	cout << "SDL with SDL_IMG and SDL_TTF initialized..." << endl << endl;

	// Initialize font
	font = TTF_OpenFont("arial.ttf", 28);
	if (font == NULL)
	{
		cout << "Failed to load font: " << TTF_GetError() << endl;
		return 1;
	}

	// Make window
	window = SDL_CreateWindow(windowName.c_str(), 300, 50, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == NULL) {
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return 1;
	}
	//screenSurface = SDL_GetWindowSurface(window);
	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0xFB, 0x1F));
	//SDL_UpdateWindowSurface(window);

	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		cout << "Failed to create renderer, details: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, bgColor.GetR(), bgColor.GetG(), bgColor.GetB(), bgColor.GetA());
	SDL_RenderClear(renderer);

	return 0;
}

std::shared_ptr<Drawable> SDLWrapper::CreateImage(std::string filename, Rect rect, bool originalSize)
{
	return CreateImage(filename, rect, Color(), originalSize);
}

// TODO Actually use status variable to check for fails before trying to use the objects
std::shared_ptr<Drawable> SDLWrapper::CreateImage(std::string filename, Rect rect, Color color, bool originalSize)
{

	SDL_Surface* imageSurface = IMG_Load(filename.c_str());
	SDL_Texture* texture = NULL;
	int status = 0;

	if (imageSurface == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		status = 1;
	}
	else
	{
		// Create a texture with this renderer
		texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

		if (texture == NULL)
		{
			std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
			status = 1;
		}
		else
		{
			// Set the rect to the dimensions of the surface if we wan't to keep the original imagefile size
			if (originalSize)
			{
				rect.w = imageSurface->w;
				rect.h = imageSurface->h;
			}

			// Free the surface after we are done with it
			SDL_FreeSurface(imageSurface);

			// Set the color of the texture
			SetTextureColor(texture, color);
		}
	}

	// If everything went right, return a new Drawable with the paramteres
	if (status == 0)
	{
		std::shared_ptr<Drawable> drawable(new Drawable(rect, texture, color));
		allDrawables.emplace_back(drawable);
		return drawable;
	}
	return NULL;
}

/* Creates an image with the specified colors and dimensions */
std::shared_ptr<Drawable> SDLWrapper::CreateRect(Color color, Rect rect)
{
	std::shared_ptr<Drawable> img = CreateImage("WhiteTexture.png", rect, false);
	img->SetColor(color);
	return img;
}

std::shared_ptr<Drawable> SDLWrapper::CreateText(std::string text, Color color, Rect rect, bool originalSize)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color.ToSDL_Color());
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
	if (originalSize)
	{
		rect.w = textSurface->w;
		rect.h = textSurface->h;
	}
	else
	{
		textSurface->w = rect.w;
		textSurface->h = rect.h;
	}
	std::shared_ptr<Drawable> drawable(new Drawable(rect, texture, color));
	allDrawables.emplace_back(drawable);
	return drawable;
}

void SDLWrapper::RenderImages(bool clearPrevious) const
{
	//SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	if (clearPrevious)
	{
		SDL_RenderClear(renderer);
	}
	for (auto i : allDrawables)
	{
		if (i->IsActive())
		{
			RenderDrawable(i);
		}
	}
	SDL_RenderPresent(renderer);
}

void SDLWrapper::Init()
{
	font = NULL;
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;
}

void SDLWrapper::DestroyImages()
{
	for (auto i : allDrawables)
	{
		// TODO possibly make Image a class with its own destructor that destroys the texture(the destructor is called when the vector is destroyed)
		SDL_DestroyTexture(i->GetTexture());
		//delete i;
	}
}

void SDLWrapper::RenderDrawable(std::shared_ptr<Drawable> drawable) const
{
	if (drawable == NULL)
	{
		std::cout << "Trying to Render a drwable that is NULL (in SDLWrapper::RenderDrawable())" << std::endl;
		return;
	}
	SDL_RenderCopy(renderer, drawable->GetTexture(), NULL, &drawable->rect.ToSDL_Rect());
}

void SDLWrapper::SetTextureColor(SDL_Texture * texture, Color color)
{
	if (SDL_SetTextureColorMod(texture, color.GetR(), color.GetG(), color.GetB()) != 0)
	{
		cout << "Failed to apply color to texture" << endl;
	}
}
