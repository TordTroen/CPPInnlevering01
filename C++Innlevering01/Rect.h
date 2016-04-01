#pragma once
#include "Vector2D.h"
#include "SDL.h"

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	float x;
	float y;
	float w;
	float h;
	bool Contains(Vector2D point);
	bool Intersects(Rect rect);
	SDL_Rect ToSDL_Rect() const;
};

