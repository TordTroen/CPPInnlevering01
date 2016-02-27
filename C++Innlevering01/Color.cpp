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
