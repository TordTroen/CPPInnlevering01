#pragma once
#include "SDL.h"
enum Colors
{
	Red,
	Yellow
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
	// TODO Implement better
	Color GetColor(Colors color)
	{
		switch (color)
		{
		case Red:
			return Color(255, 0, 0);
		case Yellow:
			return Color(200, 200, 0);
		default:
			break;
		}
	}
	SDL_Color ToSDL_Color() const;
private:
	void Set(int r, int g, int b);
	void Set(int r, int g, int b, int a);
	int _r;
	int _g;
	int _b;
	int _a;
};

