#include "Drawable.h"
#include <SDL.h>
#include <SDL_image.h>
#include "SDLWrapper.h"
#include "Transform.h"

Drawable::Drawable(Rect rect, SDL_Texture* texture, Color color)
	: _isActive(true)
{
	SetRect(rect);
	SetTexture(texture);
	_color = color;
}

Drawable::~Drawable()
{
	SDL_DestroyTexture(_texture);
}

Rect Drawable::GetRect() const
{
	if (_component == NULL)
	{
		return _rect;
	}
	else
	{
		Rect r = _component->GetTransform()->GetRect();
		if (_padding != 0)
		{
			r.Grow(_padding);
		}
		return r;
	}
}

void Drawable::SetPosition(int x, int y)
{
	_rect.x = x;
	_rect.y = y;
}

void Drawable::SetSize(int w, int h)
{
	_rect.w = w;
	_rect.h = h;
}

void Drawable::SetColor(Color color) const
{
	SDLWrapper::GetInstance().SetTextureColor(_texture, color);
}

void Drawable::SetComponent(Component * component, int padding)
{
	_component = component;
	_padding = padding;
}
