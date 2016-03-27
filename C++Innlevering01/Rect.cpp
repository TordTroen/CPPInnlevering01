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
	return (x < point.X && point.X < (x + w) && y < point.Y && point.Y < (y + h));
}

bool Rect::Intersects(Rect rect)
{
	
	return !(x + w < rect.x || x > rect.x + rect.w || y + h < rect.y || y > rect.y + rect.h);
}

SDL_Rect Rect::ToSDL_Rect() const
{
	return{ (int)x, (int)y, (int)w, (int)h }; // TODO Use C++ casting
	/*SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;*/
}
