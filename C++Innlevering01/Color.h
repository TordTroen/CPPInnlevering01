#pragma once
#include "SDL.h"
enum class Colors
{
	ColorRed,
	ColorYellow
};
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
	Color Tinted(float factor);
	Color Shaded(float factor);
	SDL_Color ToSDL_Color() const;
	bool operator==(const Color & c) const;
	bool operator!=(const Color & c) const;
private:
	void Set(int r, int g, int b);
	void Set(int r, int g, int b, int a);
	int r;
	int g;
	int b;
	int a;
};

