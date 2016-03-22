#include "Rect.h"



Rect::Rect()
	: x(0), y(0), w(0), h(0)
{
}

Rect::Rect(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool Rect::Contains(Vector2D point)
{
	return (point.X > x && point.X < x + w && point.Y < y && point.Y > y + h);
}

SDL_Rect Rect::ToSDL_Rect() const
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}
