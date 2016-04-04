#include "Theme.h"
#include "SDL_mixer.h"

Theme::Theme(int width, int height, int level)
{
	_width  = width;
	_height = height;
	_level  = level;
	Init();
}

void Theme::Init()
{
	Rect rect = Rect(0, 0, _width, _height);
	SDLWrapper::GetInstance().CreateImage(_images[_level], rect, false);
	
}
