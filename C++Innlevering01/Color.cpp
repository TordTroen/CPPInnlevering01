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
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

int Color::GetR() const { return r; }
int Color::GetG() const { return g; }
int Color::GetB() const { return b; }
int Color::GetA() const { return a; }

Color Color::Tinted(float factor)
{
	Color c(
		r + (255 - r) * factor,
		g + (255 - g) * factor,
		b + (255 - b) * factor);
	return c;
}

Color Color::Shaded(float factor)
{
	Color c(
		r * (1 - factor),
		g * (1 - factor),
		b * (1 - factor));
	return c;
}

SDL_Color Color::ToSDL_Color() const
{
	return{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a }; // TODO Use C++ casting
	/*SDL_Color c;
	c.r = _r;
	c.g = _g;
	c.b = _b;
	c.a = _a;
	return c;*/
}
