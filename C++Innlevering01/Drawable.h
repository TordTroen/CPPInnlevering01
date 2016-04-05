#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Rect.h"
#include "Color.h"
#include "Component.h"

class Drawable
{
public:
	Drawable(Rect rect, SDL_Texture* texture, Color color);
	~Drawable();
	void SetRect(Rect rect) { _rect = rect; }
	Rect GetRect() const;
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void SetTexture(SDL_Texture* texture) { _texture = texture; }
	SDL_Texture* GetTexture() const { return _texture; }
	void SetColor(Color color) const;
	Color GetColor() const { return _color; }
	void SetActive(bool active) { _isActive = active; }
	bool IsActive() const { return _isActive; }
	void SetComponent(Component* component, int padding = 0);
private:
	Component* _component;
	Rect _rect;
	SDL_Texture* _texture;
	Color _color;
	bool _isActive;
	int _padding;
};

