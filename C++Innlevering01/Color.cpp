#include "Color.h"

Color::Color()
{
	Set(255, 255, 255);
}

Color::Color(int r, int g, int b)
{
	Set(r, g, b);
}

Color::Color(int r, int g, int b, int a)
{
	Set(r, g, b, a);
}

Color::~Color()
{
}

void Color::Set(int r, int g, int b)
{
	Set(r, g, b, 255);
}

void Color::Set(int r, int g, int b, int a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

int Color::GetR() const { return _r; }
int Color::GetG() const { return _g; }
int Color::GetB() const { return _b; }
int Color::GetA() const { return _a; }

SDL_Color Color::ToSDL_Color() const
{
	return{ (Uint8)_r, (Uint8)_g, (Uint8)_b, (Uint8)_a }; // TODO Use C++ casting
	/*SDL_Color c;
	c.r = _r;
	c.g = _g;
	c.b = _b;
	c.a = _a;
	return c;*/
}
