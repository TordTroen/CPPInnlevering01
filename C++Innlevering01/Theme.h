#pragma once

#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include <iostream>
#include "GameManager.h"

#include "Drawable.h"
#include "Rect.h"
#include "SDLWrapper.h"
#include <String>

class Theme {
public:
	Theme(int height, int width, int level);
	Theme() : Theme{ 0, 0, 0 } {}
	~Theme() {}

	void Init();

private:
	int _width;
	int _height;
	int _level;
	const string _images[5]{ "brick-wall.jpg", "heaven.jpg", "WhiteTexture.png", "wonderland.jpg", "brick-wall-2.jpg" };
};

