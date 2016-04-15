#include "SDLWrapper.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm>
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

	// Initialize the different libraries
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

	// Create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "Failed to create renderer for window, details: " << SDL_GetError() << endl;
		return 1;
	}

	// Set the color of the renderer
	SDL_SetRenderDrawColor(renderer, bgColor.GetR(), bgColor.GetG(), bgColor.GetB(), bgColor.GetA());
	//SDL_RenderClear(renderer);

	return 0;
}

Drawable* SDLWrapper::CreateImage(std::string filename, Rect rect, bool originalSize, bool renderUnderneath)
{
	return CreateImage(filename, rect, Color(), originalSize, renderUnderneath);
}

Drawable* SDLWrapper::CreateImage(std::string filename, Rect rect, Color color, bool originalSize, bool renderUnderneath)
{

	SDL_Surface* imageSurface = IMG_Load(filename.c_str());
	SDL_Texture* texture = NULL;

	if (imageSurface == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
	}
	else
	{
		// Create a texture with this renderer
		texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

		if (texture == NULL)
		{
			std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
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

			// Create a new Drawable with the parameters
			Drawable* drawable = new Drawable(rect, texture, color);

			/*if (renderUnderneath)
			{
				allDrawables.emplace_front(drawable);
			}
			else
			{
				allDrawables.emplace_back(drawable);
			}*/
			AddDrawableToCollection(drawable, renderUnderneath);

			
			return drawable;
		}
	}
	return NULL;
}

/* Creates an image with the specified colors and dimensions */
Drawable* SDLWrapper::CreateRect(Color color, Rect rect, bool renderUnderneath)
{
	// Create a new image with a white blank texture
	Drawable* img = CreateImage("WhiteTexture.png", rect, false, renderUnderneath);

	// If we managed to create the image, set the color
	if (img != NULL)
	{
		img->SetColor(color);
	}
	return img;
}

Drawable* SDLWrapper::CreateText(std::string text, Color color, Rect rect, bool originalSize, bool renderUnderneath)
{
	// If the string is empty, send a warning and set the string to an empty space (because SDL doesn't render empty strings)
	if (text.empty())
	{
		cout << "WARNING: Trying to render empty text (SDL cant do that), rendering a space character instead." << endl;
		text = " ";
	}

	SDL_Texture* texture = NULL;

	// Render the text
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color.ToSDL_Color());
	if (textSurface == NULL)
	{
		cout << "Couldn't make surface for rendering text '" << text << "'." << endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			cout << "Error creating texture for text" << endl;
		}
		else
		{
			// If originalSize is true, set the rect's dimension to the imagefiles dimensions
			if (originalSize)
			{
				rect.w = textSurface->w;
				rect.h = textSurface->h;
			}
			SDL_FreeSurface(textSurface);

			// Create a new Drawable with the parameters
			Drawable* drawable = new Drawable(rect, texture, color);
			//allDrawables.emplace_back(drawable);
			AddDrawableToCollection(drawable, renderUnderneath);
			return drawable;
		}
	}
	return NULL;
}

void SDLWrapper::RenderImages(bool clearPrevious) const
{
	// Clear the renderer
	if (clearPrevious)
	{
		SDL_RenderClear(renderer);
	}

	// Renderer all the drawables that are active
	for (auto& it : allDrawables)
	{
		if (it->IsActive())
		{
			RenderDrawable(it.get());
		}
	}

	// Render the renderer to the screen so we actually see stuff
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
	// TODO Make this actually work
	for (auto& it : allDrawables)
	{
		//SDL_DestroyTexture(it->GetTexture());
		//delete i;
	}
}

void SDLWrapper::RenderDrawable(const Drawable* const drawable) const
{
	if (drawable == NULL)
	{
		std::cout << "Trying to Render a drawable that is NULL (in SDLWrapper::RenderDrawable())" << std::endl;
		return;
	}
	SDL_RenderCopy(renderer, drawable->GetTexture(), NULL, &drawable->GetRect().ToSDL_Rect());
}

void SDLWrapper::AddDrawableToCollection(Drawable * drawable, bool renderUnderneath)
{
	if (renderUnderneath)
	{
		allDrawables.emplace_front(drawable);
	}
	else
	{
		allDrawables.emplace_back(drawable);
	}
}

void SDLWrapper::SetTextureColor(SDL_Texture * texture, Color color)
{
	if (SDL_SetTextureColorMod(texture, color.GetR(), color.GetG(), color.GetB()) != 0)
	{
		cout << "Failed to apply color to texture" << endl;
	}
}

void SDLWrapper::DeleteDrawable(Drawable** drawable)
{
	allDrawables.erase(
		std::remove_if( // Selectively remove elements in the second vector...
			allDrawables.begin(),
			allDrawables.end(),
			[&](std::unique_ptr<Drawable> const& p)
			{   // This predicate checks whether the element is contained
				// in the second vector of pointers to be removed...
				return *drawable == p.get();
			}), allDrawables.end());
	*drawable = NULL;
}
