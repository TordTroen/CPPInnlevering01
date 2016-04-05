#include "Drawable.h"
#include "SDLWrapper.h"
#include <SDL.h>
#include <SDL_image.h>

Drawable::Drawable(Rect rect, SDL_Texture* texture, Color color)
	: isActive(true)
{
	SetRect(rect);
	SetTexture(texture);
	_color = color;
}


Drawable::~Drawable()
{
	SDL_DestroyTexture(texture);
}

void Drawable::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Drawable::SetSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

void Drawable::SetColor(Color color) const
{
	SDLWrapper::GetInstance().SetTextureColor(texture, color);
}
