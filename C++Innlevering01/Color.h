#pragma once
#include "SDL.h"
class Color
{
public:
	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	~Color();
	int GetR() const;
	int GetG() const;
	int GetB() const;
	int GetA() const;
	SDL_Color ToSDL_Color() const;
private:
	void Set(int r, int g, int b);
	void Set(int r, int g, int b, int a);
	int _r;
	int _g;
	int _b;
	int _a;
};

