#pragma once
#include "SDL.h"
#include "Rect.h"

class Drawable
{
public:
	Drawable(Rect rect, SDL_Texture* texture);
	~Drawable();
	Rect rect;
	void SetRect(Rect rect) { this->rect = rect; }
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void SetTexture(SDL_Texture* texture) { this->texture = texture; }
	SDL_Texture* GetTexture() const { return texture; }
private:
	SDL_Texture* texture;
};

