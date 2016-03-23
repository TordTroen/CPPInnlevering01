#include "Drawable.h"

Drawable::Drawable(Rect rect, SDL_Texture* texture)
{
	SetRect(rect);
	SetTexture(texture);
}


Drawable::~Drawable()
{
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
